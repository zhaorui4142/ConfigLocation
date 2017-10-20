#ifndef COORDFILTER_H
#define COORDFILTER_H

//ͷ�ļ�������
#include <QObject>
#include <QPointF>
#include "opencv2/opencv.hpp"


class ReaultFilter
{
public:
    ReaultFilter();
    void SetParam(int m_maxLostCount, qreal m_maxDistance);
    bool UpdateMeasure(qreal x, qreal y, qreal r);//���¿������˲���
    bool UpdateMeasure(void);//���¿������˲���
    void GetPrediction(qreal &x, qreal &y, float &r);//��ȡ����ֵ
    bool isLockedTarget(void);


private:
    //˽�к���
    bool UpdateLockState(bool add_lost_count, bool add_lock_count);
    //˽�б���
    cv::KalmanFilter KF;
    cv::Mat measurement;
    cv::Mat prediction;
    int m_maxLostCount;
    int m_lostCount;
    bool m_isLocked;
    qreal m_maxDistance;

};

#endif // COORDFILTER_H
