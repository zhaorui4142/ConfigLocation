#ifndef COORDFILTER_H
#define COORDFILTER_H

//头文件包含区
#include <QObject>
#include <QPointF>
#include "opencv2/opencv.hpp"


class ReaultFilter
{
public:
    ReaultFilter();
    void SetParam(int m_maxLostCount, qreal m_maxDistance);
    bool UpdateMeasure(qreal x, qreal y, qreal r);//更新卡尔曼滤波器
    bool UpdateMeasure(void);//更新卡尔曼滤波器
    void GetPrediction(qreal &x, qreal &y, float &r);//读取估计值
    bool isLockedTarget(void);


private:
    //私有函数
    bool UpdateLockState(bool add_lost_count, bool add_lock_count);
    //私有变量
    cv::KalmanFilter KF;
    cv::Mat measurement;
    cv::Mat prediction;
    int m_maxLostCount;
    int m_lostCount;
    bool m_isLocked;
    qreal m_maxDistance;

};

#endif // COORDFILTER_H
