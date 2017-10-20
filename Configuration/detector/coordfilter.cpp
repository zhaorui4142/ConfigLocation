#include "coordfilter.h"
#include <qmath.h>

//���캯��
ReaultFilter::ReaultFilter()
{
    m_maxLostCount = 4;
    m_maxDistance = 5;
    m_lostCount = 0;
    m_isLocked = true;

    //1.kalman filter setup
    const int stateNum=6;                                      //״ֵ̬6��1����(x,y,r,��x,��y,��r)
    const int measureNum=3;                                    //����ֵ3��1����(x,y,r)
    KF.init(stateNum, measureNum, 0);
    KF.transitionMatrix = *(cv::Mat_<float>(6, 6) <<
                            1,0,0,1,0,0,
                            0,1,0,0,1,0,
                            0,0,1,0,0,1,
                            0,0,0,1,0,0,
                            0,0,0,0,1,0,
                            0,0,0,0,0,1);   //ת�ƾ���A
    cv::setIdentity(KF.measurementMatrix);                                              //��������H
    cv::setIdentity(KF.processNoiseCov, cv::Scalar::all(1e-5));                         //ϵͳ�����������Q
    cv::setIdentity(KF.measurementNoiseCov, cv::Scalar::all(1e-1));                     //���������������R
    cv::setIdentity(KF.errorCovPost, cv::Scalar::all(1));                               //����������Э�������P
    cv::RNG rng;                                                                        //�����������
    rng.fill(KF.statePost,cv::RNG::UNIFORM,0,0.1);                                      //��ʼ״ֵ̬x(0)
    measurement = cv::Mat::zeros(measureNum, 1, CV_32F);                                //��ʼ����ֵx'(0)����Ϊ����Ҫ�������ֵ�����Ա����ȶ���
    prediction = cv::Mat::zeros(measureNum, 1, CV_32F);
}

//�趨����
void ReaultFilter::SetParam(int maxLostCount, qreal maxDistance)
{
    m_maxLostCount = maxLostCount;
    m_maxDistance = maxDistance;
}

//���²���ֵ
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

//���²���ֵ
bool ReaultFilter::UpdateMeasure()
{
    UpdateLockState(true, false);

    return m_isLocked;
}

//��ȡ����ֵ
void ReaultFilter::GetPrediction(qreal &x, qreal &y, float &r)
{
    x = prediction.at<float>(0);//Ԥ��ֵ(x',y')
    y = prediction.at<float>(1);
    r = prediction.at<float>(2);
}

//��ȡ�˲���״̬
bool ReaultFilter::isLockedTarget()
{
    return m_isLocked;
}

//�ڲ������������ڲ�״̬
bool ReaultFilter::UpdateLockState(bool add_lost_count, bool add_lock_count)
{
    //�Ѿ�����Ŀ��״̬
    if(m_isLocked)
    {
        if(add_lost_count)
        {
            m_lostCount++;
        }
        if(add_lock_count)
        {
            m_lostCount = 0;
            //�����˲���ֵ
            prediction = KF.predict();
            KF.correct(measurement);
        }
        if(m_lostCount >= m_maxLostCount)
        {
            m_isLocked = false;
            m_lostCount = 0;
        }
    }
    //û������Ŀ��״̬
    else
    {
        if(add_lock_count)
        {
            //�����˲���ֵ
            prediction = KF.predict();
            KF.correct(measurement);

            m_isLocked = true;
        }

    }

    return m_isLocked;
}

