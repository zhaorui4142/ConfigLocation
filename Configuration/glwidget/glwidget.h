#ifndef GLWIDGET_H
#define GLWIDGET_H
//ͷ�ļ�������
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QFont>
#include "struct-data.h"
#include "cpuusage/cpuusage.h"
#include "netflow/netflow.h"

//ǰ������
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLFramebufferObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QTimer)
QT_FORWARD_DECLARE_CLASS(QThread)
//struct FrameRawDataStruct;

//��������

//��ʾͼ���widget
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
    void receiveFrame(FrameRawDataStruct frame);//�����µ�ͼ��֡
    void receiveResult(DetectResultStruct result);//���ռ�������ڵ�����ʾ
    void receiveGrayscaledImageInResult(DetectResultStruct result);//���ռ����������ʾ�Ҷ�ͼ
    void receiveBluredImageInResult(DetectResultStruct result);//���ռ����������ʾ�˲����ͼ
    void receiveEdgeImageInResult(DetectResultStruct result);//���ռ����������ʾ����ͼ
    void receiveHoughImageInResult(DetectResultStruct result);//���ռ����������ʾ�����ۼ���
    void turnOnDisplay(void);//������Ƶ��ʾ
    void turnOffDisplay(void);//�ر���Ƶ��ʾ
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
    void frameConvertToTexture(FrameRawDataStruct &frame);//ͼ��֡ת������ͼ
    void resultPaintToFbo(DetectResultStruct &result);//��������Ƶ�FBO
    void drawCycleInfo(QPainter &painter, cycleInfo &cycle, QColor color);//����Բ����Ϣ
    void drawExpectRect(QPainter &painter, QPoint center, int radius, QColor color);
    void imageConverToTexture(QImage img);//QImageת������ͼ
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
