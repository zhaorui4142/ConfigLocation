#ifndef STRUCTDATA
#define STRUCTDATA

#include <QtCore>
#include <QtGui>
#include <QtDebug>


#define MAX_LOCK_COUNT 5
#define MAX_LOST_COUNT 15

//ԭʼ֡�ṹ
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

//����������ṹ
struct ParamtersForDetector//������
{
    //ͼ��Ԥ����
    QSize img_resample_size;            //ͼ�񽵲����ֱ���
    enum ImgFiltType
    {
        FILT_NONE = 0,
        FILT_BLUR = 1,
        FILT_GAUSSIAN_BLUR  = 2,
        FILT_MEDIAN  = 3,
        FILT_BILATERAL  = 4
    }img_filt_type;                     //�˲�����
    double img_filt_level;              //�˲�ǿ��

    //������
    double hough_dp;                    //���Ų���
    double min_dist;                    //Բ�ļ���С����
    double canny_threshold1;            //canny��ֵ
    double canny_threshold2;            //canny��ֵ

    double acc_threshold;               //�ۼ�����ֵ
    double radius_min;                  //������СԲ�뾶
    double radius_max;                  //�������Բ�뾶
    double brightness_max;              //�������������

    double detector_timelimit_ms;       //���һ֡ͼ����ʱ

    //��������޶�����
    bool   pos_limit_en;
    double pos_limit_left;              //�������
    double pos_limit_top;               //�������
    double pos_limit_right;             //�������
    double pos_limit_bottom;            //�������
    double expected_pos_x;              //��λ�ɹ�λ��
    double expected_pos_y;              //��λ�ɹ�λ��

    //��������˲�����
    bool   pos_filter_en;
    double pos_filter_maxCount;
    double pos_filter_maxDistance;
};

//����ͷ�����ṹ
struct ParamtersForIPCamera//cameraͨ�����ò����ṹ�嶨��
{
    QString IpAddress;//IPC IP
    QString UserName;//IPC �û���
    QString Password;//IPC ����

    bool    channalNameEN;//Ԥ����ͼ�����Ƿ���ʾͨ�����ƣ�0-����ʾ��1-��ʾ�������С704*576��
    QString channalName;//ͨ������
    int     channalNameX;//ͨ��������ʾλ�õ�x����
    int     channalNameY;//ͨ��������ʾλ�õ�y����

    bool    OSD_EN;//Ԥ����ͼ�����Ƿ���ʾOSD��0-����ʾ��1-��ʾ�������С704*576��
    int     OSD_X;//OSD��x����
    int     OSD_Y;//OSD��y����
    int     OSD_Type;//OSD����(�����ո�ʽ)��
                     //0��XXXX-XX-XX ������
                     //1��XX-XX-XXXX ������
                     //2��XXXX��XX��XX��
                     //3��XX��XX��XXXX��
                     //4��XX-XX-XXXX ������
                     //5��XX��XX��XXXX��
                     //6��xx/xx/xxxx ��/��/��
                     //7��xxxx/xx/xx ��/��/��
                     //8��xx/xx/xxxx ��/��/��
    bool    OSD_DispWeekEN;//�Ƿ���ʾ���ڣ�0-����ʾ��1-��ʾ
    int     OSD_HourOSDType;//Сʱ�ƣ�0��ʾ24Сʱ�ƣ�1��ʾ12Сʱ�ƻ�am/pm
    int     OSD_FontSize;//�����С��0- 16*16(��)/8*16(Ӣ)��1- 32*32(��)/16*32(Ӣ)��2- 64*64(��)/32*64(Ӣ)��3- 48*48(��)/24*48(Ӣ)��0xff-����Ӧ(adaptive)
    long    OSD_Color;//������ɫ
};

//���������ṹ
struct cycleInfo
{
    QPointF centerPoint;
    float   radius;
    int     accumCount;
    float   accumIntensity;
    int     brightness;
};

//�����
struct DetectResultStruct
{
    //ԭͼ
    FrameRawDataStruct rawFrame;

    //������Ϣ������м���
    int count_nz;
    int count_possible_center;

    //���ռ����
    std::vector<cycleInfo> satisfiedCycles;//�������
    int theBestCycleIndex;//���ŵĽ��λ��

    //������Ϣ��CPUʹ����
    QVector<int> cpu_usage;

    //������Ϣ����ʱ
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

    //����ͼ��
    QImage imgROI;
    QImage imgBlured;
    QImage imgEdges;
    QImage imgHistogram;
    QImage imgAccum;

    //����������Ϣ
    int count_used_thread;
    QSize resampleSize; //ͼ�񽵲����ֱ���
    bool   pos_limit_en;
    QRect  ROIRect;
    QPointF expectCenterPoint;
    double radius_max;  //�������Բ�뾶
};





#endif // STRUCTDATA

