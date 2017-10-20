#include "coordfilter.h"
#include <qmath.h>

//构造函数
ReaultFilter::ReaultFilter()
{
    m_maxLostCount = 4;
    m_maxDistance = 5;
    m_lostCount = 0;
    m_isLocked = true;

    //1.kalman filter setup
    const int stateNum=6;                                      //状态值6×1向量(x,y,r,△x,△y,△r)
    const int measureNum=3;                                    //测量值3×1向量(x,y,r)
    KF.init(stateNum, measureNum, 0);
    KF.transitionMatrix = *(cv::Mat_<float>(6, 6) <<
                            1,0,0,1,0,0,
                            0,1,0,0,1,0,
                            0,0,1,0,0,1,
                            0,0,0,1,0,0,
                            0,0,0,0,1,0,
                            0,0,0,0,0,1);   //转移矩阵A
    cv::setIdentity(KF.measurementMatrix);                                              //测量矩阵H
    cv::setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));                         //系统噪声方差矩阵Q
    cv::setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-1));                     //测量噪声方差矩阵R
    cv::setIdentity(KF.errorCovPost, cv::Scalar::all(1));                               //后验错误估计协方差矩阵P
    cv::RNG rng;                                                                        //随机数生成器
    rng.fill(KF.statePost,cv::RNG::UNIFORM,0,0.1);                                      //初始状态值x(0)
    measurement = cv::Mat::zeros(measureNum, 1, CV_32F);                                //初始测量值x'(0)，因为后面要更新这个值，所以必须先定义
    prediction = cv::Mat::zeros(measureNum, 1, CV_32F);
}

//设定参数
void ReaultFilter::SetParam(int maxLostCount, qreal maxDistance)
{
    m_maxLostCount = maxLostCount;
    m_maxDistance = maxDistance;
}

//更新测量值
bool ReaultFilter::UpdateMeasure(qreal x, qreal y, qreal r)
{
    qreal x0 = prediction.at<float>(0);
    qreal y0 = prediction.at<float>(1);
    qreal distance = qSqrt(qPow((x-x0),2) + qPow((y-y0),2));

    //update measurement
    measurement.at<float>(0) = (float)x;
    measurement.at<float>(1) = (float)y;
    measurement.at<float>(2) = (float)r;

    if(distance >= m_maxDistance)
        UpdateLockState(true, false);
    else
        UpdateLockState(false, true);

    return m_isLocked;
}

//更新测量值
bool ReaultFilter::UpdateMeasure()
{
    UpdateLockState(true, false);

    return m_isLocked;
}

//读取评估值
void ReaultFilter::GetPrediction(qreal &x, qreal &y, float &r)
{
    x = prediction.at<float>(0);//预测值(x',y')
    y = prediction.at<float>(1);
    r = prediction.at<float>(2);
}

//读取滤波器状态
bool ReaultFilter::isLockedTarget()
{
    return m_isLocked;
}

//内部函数，计算内部状态
bool ReaultFilter::UpdateLockState(bool add_lost_count, bool add_lock_count)
{
    //已经锁定目标状态
    if(m_isLocked)
    {
        if(add_lost_count)
        {
            m_lostCount++;
        }
        if(add_lock_count)
        {
            m_lostCount = 0;
            //更新滤波器值
            prediction = KF.predict();
            KF.correct(measurement);
        }
        if(m_lostCount >= m_maxLostCount)
        {
            m_isLocked = false;
            m_lostCount = 0;
        }
    }
    //没有锁定目标状态
    else
    {
        if(add_lock_count)
        {
            //更新滤波器值
            prediction = KF.predict();
            KF.correct(measurement);

            m_isLocked = true;
        }

    }

    return m_isLocked;
}

