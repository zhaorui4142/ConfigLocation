#ifndef STRUCTDATA
#define STRUCTDATA

#include <QtCore>
#include <QtGui>
#include <QtDebug>


#define MAX_LOCK_COUNT 5
#define MAX_LOST_COUNT 15

//原始帧结构
struct FrameRawDataStruct
{
    QByteArray imgData;
    int dataLength;
    int imgWidth;
    int imgHeigh;
    int frameRate;
    long frameNum;
    long frameStamp;
};

//检测器参数结构
struct ParamtersForDetector//检测参数
{
    //图像预处理
    QSize img_resample_size;            //图像降采样分辨率
    enum ImgFiltType
    {
        FILT_NONE = 0,
        FILT_BLUR = 1,
        FILT_GAUSSIAN_BLUR  = 2,
        FILT_MEDIAN  = 3,
        FILT_BILATERAL  = 4
    }img_filt_type;                     //滤波类型
    double img_filt_level;              //滤波强度

    //检测参数
    double hough_dp;                    //缩放参数
    double min_dist;                    //圆心间最小距离
    double canny_threshold1;            //canny阈值
    double canny_threshold2;            //canny阈值

    double acc_threshold;               //累加量阈值
    double radius_min;                  //检测的最小圆半径
    double radius_max;                  //检测的最大圆半径
    double brightness_max;              //罐中心最高亮度

    double detector_timelimit_ms;       //检测一帧图像限时

    //检测坐标限定参数
    bool   pos_limit_en;
    double pos_limit_left;              //检测区域
    double pos_limit_top;               //检测区域
    double pos_limit_right;             //检测区域
    double pos_limit_bottom;            //检测区域
    double expected_pos_x;              //对位成功位置
    double expected_pos_y;              //对位成功位置

    //结果坐标滤波参数
    bool   pos_filter_en;
    double pos_filter_maxCount;
    double pos_filter_maxDistance;
};

//摄像头参数结构
struct ParamtersForIPCamera//camera通道设置参数结构体定义
{
    QString IpAddress;//IPC IP
    QString UserName;//IPC 用户名
    QString Password;//IPC 密码

    bool    channalNameEN;//预览的图象上是否显示通道名称：0-不显示，1-显示（区域大小704*576）
    QString channalName;//通道名称
    int     channalNameX;//通道名称显示位置的x坐标
    int     channalNameY;//通道名称显示位置的y坐标

    bool    OSD_EN;//预览的图象上是否显示OSD：0-不显示，1-显示（区域大小704*576）
    int     OSD_X;//OSD的x坐标
    int     OSD_Y;//OSD的y坐标
    int     OSD_Type;//OSD类型(年月日格式)：
                     //0－XXXX-XX-XX 年月日
                     //1－XX-XX-XXXX 月日年
                     //2－XXXX年XX月XX日
                     //3－XX月XX日XXXX年
                     //4－XX-XX-XXXX 日月年
                     //5－XX日XX月XXXX年
                     //6－xx/xx/xxxx 月/日/年
                     //7－xxxx/xx/xx 年/月/日
                     //8－xx/xx/xxxx 日/月/年
    bool    OSD_DispWeekEN;//是否显示星期：0-不显示，1-显示
    int     OSD_HourOSDType;//小时制：0表示24小时制，1表示12小时制或am/pm
    int     OSD_FontSize;//字体大小：0- 16*16(中)/8*16(英)，1- 32*32(中)/16*32(英)，2- 64*64(中)/32*64(英)，3- 48*48(中)/24*48(英)，0xff-自适应(adaptive)
    long    OSD_Color;//字体颜色
};

//检测器结果结构
struct cycleInfo
{
    QPointF centerPoint;
    float   radius;
    int     accumCount;
    float   accumIntensity;
    int     brightness;
};

//检测结果
struct DetectResultStruct
{
    //原图
    FrameRawDataStruct rawFrame;

    //附加信息，检测中间结果
    int count_nz;
    int count_possible_center;

    //最终检测结果
    std::vector<cycleInfo> satisfiedCycles;//结果数组
    int theBestCycleIndex;//最优的结果位置

    //附加信息，CPU使用率
    QVector<int> cpu_usage;

    //附加信息，耗时
    qreal elapsed_ms_scale;
    qreal elapsed_ms_blur;
    qreal elapsed_ms_canny;
    qreal elapsed_ms_histogram;
    qreal elapsed_ms_sobel;
    qreal elapsed_ms_accum;
    qreal elapsed_ms_findPossibleCenter;
    qreal elapsed_ms_sortPossibleCenter;
    qreal elapsed_ms_checkPossibleCenter;
    qreal elapsed_ms_total;

    //附加图像
    QImage imgROI;
    QImage imgBlured;
    QImage imgEdges;
    QImage imgHistogram;
    QImage imgAccum;

    //其他附加信息
    int count_used_thread;
    QSize resampleSize; //图像降采样分辨率
    bool   pos_limit_en;
    QRect  ROIRect;
    QPointF expectCenterPoint;
    double radius_max;  //检测的最大圆半径
};





#endif // STRUCTDATA

