#ifndef HOLEDETECTOR_H
#define HOLEDETECTOR_H

//----------------模块功能说明--------------------
//Detector类负责与外部连接：接收图像，发送结果
//Detector类每接收一个图像就生成一个Worker类的对象，并启动一个线程
//检测结束以后将结果用信号发出去，并自动销毁Worker对象。
//-----------------------------------------------

//头文件包含区
#include <QObject>
#include <QList>
#include <QThread>
#include <windows.h>
#include "opencv2/opencv.hpp"
#include "struct-data.h"
#include "coordfilter.h"



//检测器，负责接收图像，利用多线程计算，发送结果
class Detector : public QObject
{
    Q_OBJECT

public:
    Detector(ParamtersForDetector &param,  QObject *parent = 0);
    void setParam(ParamtersForDetector &param);
    ~Detector(void);

signals:
    //检测完毕信号
    void resultReady(DetectResultStruct result);

public slots:
    //接收图像槽函数
    void receiveFrame(FrameRawDataStruct frame);

private slots:
    //接收子线程发来的检测完毕信号
    void receiveResult(DetectResultStruct result);

private:
    //私有成员函数

    //私有变量
    ParamtersForDetector param;
    QThreadPool *thread_pool;
    ReaultFilter filter;
};

//计算单元
class Worker : public QObject, public QRunnable
{
    Q_OBJECT

signals:
    void resultReady(DetectResultStruct result);

public:
    Worker(ParamtersForDetector param, FrameRawDataStruct frame, QObject *parent = 0);
    ~Worker(void);
    void run();

private:
    void findCircles(cv::Mat &img, DetectResultStruct &result);
    void icvHoughSortDescent32s(int *array, size_t total, const int* aux);
    void icvHoughSortDescent32f(int *array, size_t total, const float* aux);
    bool coordinateConversion(QPointF &coord_roi, QPointF &coord_src);

    QImage MatCopy2QImage(const cv::Mat &mat);
    QImage MatScaled2QImage(const cv::Mat &mat,double dp);
    cv::MatND getHistogram(const cv::Mat &image);
    QImage Histogram2QImage(const cv::Mat &hist);
    int thresholdOtsu(cv::Mat &img,cv::MatND &histogram);
    qreal getIntervalMillisecond();
    qreal getLivedMillisecond();

    //私有成员
    ParamtersForDetector param;
    FrameRawDataStruct frame;
    LARGE_INTEGER t1,t2,tc,t_start,t_current;

};


#endif // HOLEDETECTOR_H
