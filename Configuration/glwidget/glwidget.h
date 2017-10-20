#ifndef GLWIDGET_H
#define GLWIDGET_H
//头文件包含区
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QFont>
#include "struct-data.h"
#include "cpuusage/cpuusage.h"
#include "netflow/netflow.h"

//前置声明
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QThread)
//struct FrameRawDataStruct;

//类声明区

//显示图像的widget
class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GlWidget(QWidget *parent = 0);
    ~GlWidget();
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void cleanup();
    void receiveFrame(FrameRawDataStruct frame);//接收新的图像帧
    void receiveResult(DetectResultStruct result);//接收检测结果用于叠加显示
    void receiveGrayscaledImageInResult(DetectResultStruct result);//接收检测结果用于显示灰度图
    void receiveBluredImageInResult(DetectResultStruct result);//接收检测结果用于显示滤波后的图
    void receiveEdgeImageInResult(DetectResultStruct result);//接收检测结果用于显示轮廓图
    void receiveHoughImageInResult(DetectResultStruct result);//接收检测结果用于显示霍夫累加器
    void turnOnDisplay(void);//开启视频显示
    void turnOffDisplay(void);//关闭视频显示
    bool isDisplayAlreadyTurnOn(void);

signals:
    void visableChanged(bool isVisable);
    void posChanged(qreal top, qreal bottom, qreal left, qreal right, qreal exp_x, qreal exp_y);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent * event) Q_DECL_OVERRIDE;

private:
    void frameConvertToTexture(FrameRawDataStruct &frame);//图像帧转换成贴图
    void resultPaintToFbo(DetectResultStruct &result);//检测结果绘制到FBO
    void drawCycleInfo(QPainter &painter, cycleInfo &cycle, QColor color);//绘制圆的信息
    void drawExpectRect(QPainter &painter, QPoint center, int radius, QColor color);
    void imageConverToTexture(QImage img);//QImage转换成贴图
    bool isDisplayTurnOn;
    bool displayFrameReady;
    bool displayResultReady;
    bool displayQImageReady;
    QPoint m_lastPos;
    QRect m_expectRect;
    QRect m_roiRect;
    bool m_expectCatched;
    bool m_roiLeftCatched;
    bool m_roiRightCatched;
    bool m_roiUpCatched;
    bool m_roiDownCatched;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *program_frame;
    QOpenGLShaderProgram *program_result;
    QOpenGLShaderProgram *program_qimage;
    QOpenGLTexture *texture_y, *texture_u, *texture_v;
    QOpenGLFunctions *glFunctions;
    QOpenGLFramebufferObject *fbo;
    QSize displaySize;
    QFont font_fbo1,font_fbo_title;
    NetFlow *net_flow;
    CpuUsage *cpu_usage;
};





#endif // GLWIDGET_H
