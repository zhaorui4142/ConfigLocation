//ͷ�ļ�������
#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QCoreApplication>
#include <QTimer>
#include <QtGui>
#include <QThread>
#include <QFontDatabase>
#include <QDebug>

//�궨����
#define ATTRIB_VERTEX 0
#define ATTRIB_TEXTURE 1
#define ATTRIB_TEXTURE_INTRV 2
#define BUFFER_OFFSET(offset) ((GLvoid *) (reinterpret_cast<void *>(offset)))



//=============================================================================================//
//==============================����Ϊ��GlWidget���ʵ��==========================================//


//GlWidget�๹�캯��
GlWidget::GlWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program_frame(0),
      isDisplayTurnOn(false),
      displayFrameReady(false),
      displayResultReady(false),
      displayQImageReady(false),
      fbo(0)
{
    //��������
    int index = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath()+"/fonts/YaHeiConsolas.ttf");
    if(index != -1)
    {
        QStringList list(QFontDatabase::applicationFontFamilies(index));
        if(list.count()>0)
        {
            font_fbo1.setFamily(list.at(0));
            font_fbo1.setPointSize(8);
            font_fbo1.setBold(true);
        }
    }
    index = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath()+"/fonts/YaHeiConsolas.ttf");
    if(index != -1)
    {
        QStringList list(QFontDatabase::applicationFontFamilies(index));
        if(list.count()>0)
        {
            font_fbo_title.setFamily(list.at(0));
            font_fbo_title.setPointSize(10);
            font_fbo_title.setBold(true);
        }
    }
    cpu_usage = new CpuUsage;
    net_flow = new NetFlow;
}

//GlWidget����������
GlWidget::~GlWidget()
{
    cleanup();
    delete cpu_usage;
    delete net_flow;
}

//OpenGl���غ�������ʼ��
void GlWidget::initializeGL()
{
    const int numVertices = 24;
    //�������ٺ��ͷ�opengl��Դ
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GlWidget::cleanup);

    //��ʼ��OpenGL����
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1.0);

    //�趨opengl functionָ��
    glFunctions = context()->functions();

    //��ʼ��texture
    texture_y         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_u         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_v         = new QOpenGLTexture(QOpenGLTexture::Target2D);

    //��ʼ�������������VAO��
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //װ�仺�����VBO��
    static const GLfloat vertices[numVertices] = {
        //vertexVertices��������
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        //textureVertices�������� 1
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        //textureVertices�������� 2
        0.0f,  0.0f,
        1.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f
    };
    m_vbo.create();                                            //glGenBuffers
    m_vbo.bind();                                              //glBindBuffer
    m_vbo.allocate(vertices, numVertices * sizeof(GLfloat));   //blBUfferData

    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    glEnableVertexAttribArray(ATTRIB_TEXTURE_INTRV);
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(GLfloat)));
    glVertexAttribPointer(ATTRIB_TEXTURE_INTRV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(16 * sizeof(GLfloat)));
    m_vbo.release();

    //����program����,(������ָ��Դ�롢����shader)
    program_frame = new QOpenGLShaderProgram;
    program_frame->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/yv12Display.vsh");
    program_frame->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/yv12Display.fsh");
    program_frame->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_frame->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_result = new QOpenGLShaderProgram;
    program_result->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/yv12DisplayWithOverlay.vsh");
    program_result->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/yv12DisplayWithOverlay.fsh");
    program_result->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_result->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_result->bindAttributeLocation("textureIn_fbo", ATTRIB_TEXTURE_INTRV);
    program_qimage = new QOpenGLShaderProgram;
    program_qimage->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/previewgrayscale.vsh");
    program_qimage->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/previewgrayscale.fsh");
    program_qimage->bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program_qimage->bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program_qimage->bindAttributeLocation("textureIn_fbo", ATTRIB_TEXTURE_INTRV);
}

//OpenGl���غ�������ͼ
void GlWidget::paintGL()
{
    //�����Ļ����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!isDisplayTurnOn) return;
    if(displayFrameReady)
    {
        //��vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //��program
        program_frame->bind();//�൱��glUseProgram
        program_frame->setUniformValue("tex_y", 1);
        program_frame->setUniformValue("tex_u", 2);
        program_frame->setUniformValue("tex_v", 3);

        //����ͼ
        texture_y->bind(1);
        texture_u->bind(2);
        texture_v->bind(3);

        //����ͼ��
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        program_frame->release();
    }
    if(displayResultReady)
    {
        //��vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //��program
        program_result->bind();//�൱��glUseProgram
        program_result->setUniformValue("tex_y", 1);
        program_result->setUniformValue("tex_u", 2);
        program_result->setUniformValue("tex_v", 3);
        program_result->setUniformValue("tex_overlay", 4);

        //����ͼ
        texture_y->bind(1);
        texture_u->bind(2);
        texture_v->bind(3);
        GLuint tex_OSD = fbo->texture();
        QOpenGLFramebufferObject::bindDefault();
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, tex_OSD);

        //�ı��ӿ�
        glViewport(0,0,width(),height());

        //����ͼ��
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        program_result->release();
    }
    if(displayQImageReady)
    {
        //��vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //��program
        program_qimage->bind();//�൱��glUseProgram
        program_qimage->setUniformValue("tex_y", 1);

        //����ͼ
        texture_y->bind(1);

        //����ͼ��
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        program_qimage->release();
    }

}

//OpenGl���غ������ı䴰�ڴ�С
void GlWidget::resizeGL(int w, int h)
{
/*
    //��ͼ��ֱ���Ϊ4����������������ʾʱ����ë��
    int w1=w/4;
    int h1=h/4;

    //��ͼ����16:9�ı�����ʾ������λ����ʾ�ڵ�
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //�滻��������
    GLfloat x=(GLfloat)(w1*4)/(GLfloat)w;
    GLfloat y=(GLfloat)(h1*4)/(GLfloat)h;

    if(w1*9 > h1*16)    x = (h1*16.0f)/(w1*9.0f);
    else                y = (w1*9.0)/(h1*16.0f);

    displaySize.setWidth(w*x);
    displaySize.setHeight(h*y);

    const GLfloat vertices[8] = {-x, -y,//vertexVertices��������
                                  x, -y,
                                 -x,  y,
                                  x,  y};

    m_vbo.bind();                                  //glBindBuffer
    m_vbo.write(0, vertices, 8* sizeof(GLfloat));  //blBUfferData
    m_vbo.release();
    */

    displaySize.setWidth(w);
    displaySize.setHeight(h);
}

//˽�к��������ͼ��
void GlWidget::cleanup()
{
    makeCurrent();
    m_vbo.destroy();
    texture_y->destroy();
    texture_u->destroy();
    texture_v->destroy();
    delete texture_y;
    delete texture_u;
    delete texture_v;
    program_frame->deleteLater();
    program_result->deleteLater();
    program_qimage->deleteLater();
    delete fbo;
    doneCurrent();
}

//���вۺ����������µ�ͼ��֡������ͼ������ת��Ϊ��ͼ
void GlWidget::receiveFrame(FrameRawDataStruct frame)
{
    if(isDisplayTurnOn)
    {
        //ת������ͼ
        frameConvertToTexture(frame);
        //��λ��ʾ��־
        displayResultReady = false;
        displayFrameReady = true;
        displayQImageReady = false;
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//���ռ��������ʾ
void GlWidget::receiveResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //����fbo
        resultPaintToFbo(result);
        //ת������ͼ
        frameConvertToTexture(result.rawFrame);
        //��λ��ʾ��־
        displayFrameReady = false;
        displayResultReady = true;
        displayQImageReady = false;
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//���ռ�����еĻҶ�ͼ�ۺ���
void GlWidget::receiveGrayscaledImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //ת������ͼ
        imageConverToTexture(result.imgROI);
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//���ռ�����е�ͼ�ۺ���
void GlWidget::receiveBluredImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //ת������ͼ
        imageConverToTexture(result.imgBlured);
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//���ռ�����е�ͼ�ۺ���
void GlWidget::receiveEdgeImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //ת������ͼ
        imageConverToTexture(result.imgEdges);
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//���ռ�����е�ͼ�ۺ���
void GlWidget::receiveHoughImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //ת������ͼ
        imageConverToTexture(result.imgAccum);
        //ˢ��ͼ��
        update();
    }
    else
        return;
}

//ͼ��֡ת������ͼ
void GlWidget::frameConvertToTexture(FrameRawDataStruct &frame)
{
    //�������������ָ��
    // yv12���ݸ�ʽ������Y��������Ϊwidth * height, U��V�������ȶ�Ϊwidth * height / 4
    int nYLen = frame.imgWidth * frame.imgHeigh;
    char* yData = frame.imgData.data();
    char* vData = &yData[nYLen];
    char* uData = &vData[nYLen>>2];
    if(!uData || !vData) return;

    glFunctions->glFlush();
    makeCurrent();
    //���������������ϴ���������
    //y
    if(!texture_y->isStorageAllocated())
    {
        texture_y->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_y->setMinificationFilter(QOpenGLTexture::Linear);
        texture_y->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_y->setFormat(QOpenGLTexture::R8_UNorm);
        texture_y->setSize(frame.imgWidth, frame.imgHeigh);
        texture_y->allocateStorage();
    }
    texture_y->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(yData));

    //u
    if(!texture_u->isStorageAllocated())
    {
        texture_u->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_u->setMinificationFilter(QOpenGLTexture::Linear);
        texture_u->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_u->setFormat(QOpenGLTexture::R8_UNorm);
        texture_u->setSize(frame.imgWidth/2, frame.imgHeigh/2);
        texture_u->allocateStorage();
    }
    texture_u->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(uData));
    //v
    if(!texture_v->isStorageAllocated())
    {
        texture_v->setMagnificationFilter(QOpenGLTexture::Linear);
        texture_v->setMinificationFilter(QOpenGLTexture::Linear);
        texture_v->setWrapMode(QOpenGLTexture::ClampToBorder);
        texture_v->setFormat(QOpenGLTexture::R8_UNorm);
        texture_v->setSize(frame.imgWidth/2, frame.imgHeigh/2);
        texture_v->allocateStorage();
    }
    texture_v->setData(QOpenGLTexture::Red, QOpenGLTexture::UInt8, reinterpret_cast<void *>(vData));

    //glFunctions->glFlush();
}

//��������Ƶ�fbo��
void GlWidget::resultPaintToFbo(DetectResultStruct &result)
{
    //1.�л�����ǰwidget��context
    glFunctions->glFlush();
    makeCurrent();

    //2.׼��fbo
    if(fbo == NULL)
        fbo = new QOpenGLFramebufferObject(displaySize, QOpenGLFramebufferObject::CombinedDepthStencil);
    if(fbo->size() != displaySize)
    {
        fbo->release();
        delete fbo;
        fbo = new QOpenGLFramebufferObject(displaySize, QOpenGLFramebufferObject::CombinedDepthStencil);
    }
    fbo->bind();

    //3.���FBO
    glFunctions->glClearColor(0.0, 0.0, 0.0, 0.0);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //4.��ʼ����
    QOpenGLPaintDevice device(fbo->size());
    QPainter painter;
    painter.begin(&device);
    QColor textColor(255, 255, 255, 255);//������ɫ
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

    //5.���Ƽ������
    if(result.pos_limit_en)
    {
        int left = (result.ROIRect.left() * this->width())/100;
        int right = (result.ROIRect.right() * this->width())/100;
        int top = (result.ROIRect.top() * this->height())/100;
        int bottom = (result.ROIRect.bottom() * this->height())/100;

        QPen pen(QColor(0,255,0,255));
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(left, top, right-left, bottom-top);
        m_roiRect = QRect(left, top, right-left, bottom-top);
    }
    else
    {
        m_roiRect = QRect();
    }

    //6.���Ʋ�����Ϣ
    //6.1ͼ�����
    QPoint textPoint(10,20);
    painter.setPen(textColor);
    painter.setBrush(QBrush(QColor(64, 64, 64, 128)));
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 102);
    painter.setFont(font_fbo1);
    painter.drawText(8, 16, QString::fromLocal8Bit("ͼ�������"));
    painter.drawText(8, 32, QString::fromLocal8Bit("ԭ  ʼ��")+QString::number(result.rawFrame.imgWidth)+"x"+QString::number(result.rawFrame.imgHeigh));
    painter.drawText(8, 48, QString::fromLocal8Bit("��������")+QString::number(result.resampleSize.width())+"x"+QString::number(result.resampleSize.height()));
    painter.drawText(8, 64, QString::fromLocal8Bit("��  �ڣ�")+QString::number(this->width())+"x"+QString::number(this->height()));
    painter.drawText(8, 80, QString::fromLocal8Bit("ROI   ��")+QString::number(result.imgROI.width())+"x"+QString::number(result.imgROI.height()));
    painter.drawText(8, 96, QString::fromLocal8Bit("֡  �ʣ�")+QString::number(result.rawFrame.frameRate)+"fps");
    painter.restore();

    //6.2����
    textPoint = QPoint(10,140);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 182);
    painter.setFont(font_fbo1);
    painter.drawText(8,  16, QString::fromLocal8Bit("���ܣ�"));
    painter.drawText(8,  32, QString::fromLocal8Bit("���߳�����")+QString::number(result.count_used_thread));
    painter.drawText(8,  48, QString::fromLocal8Bit("ͼ�����ţ�")+QString::number(result.elapsed_ms_scale, 'f', 2)+"ms");
    painter.drawText(8,  64, QString::fromLocal8Bit("ͼ���˲���")+QString::number(result.elapsed_ms_blur, 'f', 2)+"ms");
    painter.drawText(8,  80, QString::fromLocal8Bit("����������")+QString::number(result.elapsed_ms_canny, 'f', 2)+"ms");
    painter.drawText(8,  96, QString::fromLocal8Bit("ֱ��ͼ  ��")+QString::number(result.elapsed_ms_histogram, 'f', 2)+"ms");
    painter.drawText(8, 112, QString::fromLocal8Bit("����任��")+QString::number(result.elapsed_ms_accum, 'f', 2)+"ms");
    painter.drawText(8, 128, QString::fromLocal8Bit("����Բ�ģ�")+QString::number(result.elapsed_ms_findPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 144, QString::fromLocal8Bit("�������")+QString::number(result.elapsed_ms_sortPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 160, QString::fromLocal8Bit("���ɸѡ��")+QString::number(result.elapsed_ms_checkPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 176, QString::fromLocal8Bit("�ܺ�ʱ  ��")+QString::number(result.elapsed_ms_total, 'f', 2)+"ms");
    painter.restore();

    //6.3�����
    textPoint = QPoint(10,340);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 166);
    painter.setFont(font_fbo1);
    painter.drawText(0, 16, QString::fromLocal8Bit("Ŀ���⣺"));
    painter.drawText(4,  32, QString::fromLocal8Bit("��Ե���ص�����")+QString::number(result.count_nz));
    painter.drawText(4,  48, QString::fromLocal8Bit("���ܵ�Ŀ������")+QString::number(result.count_possible_center));
    painter.drawText(4,  64, QString::fromLocal8Bit("ɸѡ��Ŀ������")+QString::number(result.satisfiedCycles.size()));
    if(result.satisfiedCycles.size() !=0 )
    {
        cycleInfo &best = result.satisfiedCycles[result.theBestCycleIndex];
        painter.drawText(4,  80, QString::fromLocal8Bit("����Բ�����꣺X")+QString::number(best.centerPoint.x(), 'f', 0));
        painter.drawText(4,  96, QString::fromLocal8Bit("����Բ�����꣺Y")+QString::number(best.centerPoint.y(), 'f', 0));
        painter.drawText(4, 112, QString::fromLocal8Bit("����Բ�뾶  ��")+QString::number(best.radius, 'f', 2));
        painter.drawText(4, 128, QString::fromLocal8Bit("����Բ�����ȣ�")+QString::number(best.brightness));
        painter.drawText(4, 144, QString::fromLocal8Bit("����Բhough ��")+QString::number(best.accumCount));
        painter.drawText(4, 158, QString::fromLocal8Bit("����Բ�����ȣ�")+QString::number(best.accumIntensity, 'f', 2));
    }
    else
    {
        painter.drawText(4,  80, QString::fromLocal8Bit("����Բ�����꣺X"));
        painter.drawText(4,  96, QString::fromLocal8Bit("����Բ�����꣺Y"));
        painter.drawText(4, 112, QString::fromLocal8Bit("����Բ�뾶  ��"));
        painter.drawText(4, 128, QString::fromLocal8Bit("����Բ�����ȣ�"));
        painter.drawText(4, 144, QString::fromLocal8Bit("����Բhough ��"));
        painter.drawText(4, 158, QString::fromLocal8Bit("����Բ�����ȣ�"));
    }
    painter.restore();

    //6.4CPUʹ����
    textPoint = QPoint(800,84);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 128, 88+68*((cpu_usage->GetNumberProcessors()/4)-1));
    painter.setFont(font_fbo1);
    painter.drawText(4, 16, QString::fromLocal8Bit("CPU��"));
    for(int i=0; i<cpu_usage->GetNumberProcessors(); i++)
    {
        painter.drawText(4, 16*(i+2), "CPU"+QString::number(i)+":"+QString::number(cpu_usage->GetUseage(i))+"%");
    }
    painter.restore();

    //6.5����������
    textPoint = QPoint(800,20);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 128, 54);
    painter.setFont(font_fbo1);
    painter.drawText(4, 16, QString::fromLocal8Bit("���磺"));
    painter.drawText(4, 32,QString::fromLocal8Bit("�ϴ�:") + QString::number(net_flow->getUploadingSpeed())+"kbps");
    painter.drawText(4, 48,QString::fromLocal8Bit("����:") + QString::number(net_flow->getDownloadingSpeed())+"kbps");
    painter.restore();

    //6.6ֱ��ͼ
    textPoint = QPoint(800,460);
    painter.save();
    painter.translate(textPoint);
    QImage histImg = result.imgHistogram;
    if(!histImg.isNull())
    {
        painter.setPen(QColor(255,255,255,255));
        painter.drawRect(0, 0, histImg.width()/2, histImg.height()/2);
        painter.setFont(font_fbo_title);
        painter.drawText(0, -4, QString::fromLocal8Bit("ֱ��ͼ��"));
        painter.drawImage(0, 0, histImg.scaled(128,64));
    }
    painter.restore();

    //7.���Ƽ����
    //7.1���Ƽ�⵽��Բ
    for(uint i=0; i<result.satisfiedCycles.size(); i++)
    {
        cycleInfo cycle = result.satisfiedCycles[i];
        cycle.centerPoint = QPoint(cycle.centerPoint.x()*width()/result.rawFrame.imgWidth, cycle.centerPoint.y()*height()/result.rawFrame.imgHeigh);
        if(i == result.theBestCycleIndex)
            drawCycleInfo(painter, cycle, QColor(0, 255, 0, 255));
        else
            drawCycleInfo(painter, cycle, QColor(255, 0, 0, 255));
    }

    //7.2����Ŀ��λ��
    QPoint ExceptCenter;
    ExceptCenter.setX(result.expectCenterPoint.x()*this->width()/result.rawFrame.imgWidth);
    ExceptCenter.setY(result.expectCenterPoint.y()*this->height()/result.rawFrame.imgHeigh);
    drawExpectRect(painter, ExceptCenter, result.radius_max, QColor(0, 255, 0, 255));

    //7.7����������
    //painter.drawLine(QPoint(200,200),ExceptCenter);


    //8.���ƽ���
    painter.end();

}

//���Ƽ�⵽��Բ
void GlWidget::drawCycleInfo(QPainter &painter, cycleInfo &cycle, QColor color)
{
    QPoint center(cycle.centerPoint.x(), cycle.centerPoint.y());
    int radius = cycle.radius;
    QPoint cycleOffset(radius, radius);
    QPoint intensityOffset(radius-2, radius-2);
    QPoint textPoint(cycle.centerPoint.x()+radius+5, cycle.centerPoint.y()-radius-5);
    float &intensity = cycle.accumIntensity;
    int &hough = cycle.accumCount;
    int &bright = cycle.brightness;

    QRect cycleRect(center-cycleOffset, center+cycleOffset);
    QRect intensityRect(center-intensityOffset, center+intensityOffset);
    QPen pen(color);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(cycleRect);
    painter.drawLine(center+QPoint(radius/1.4, -radius/1.4), textPoint);
    painter.drawLine(textPoint, textPoint + QPoint(60,0));
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawArc(intensityRect, 90*16, intensity*(-360.0)*16);
    painter.setFont(font_fbo1);
    painter.drawText(textPoint+QPoint(0,10), "x=" + QString::number(center.x()) +
                                                        " y=" + QString::number(center.y()) +
                                                        " r=" + QString::number(radius));
    painter.drawText(textPoint+QPoint(0,22), "hough="+QString::number(hough));
    painter.drawText(textPoint+QPoint(0,34), "bright="+QString::number(bright));
    painter.drawText(textPoint+QPoint(0,46), QString::fromLocal8Bit("dx=100 dy=200"));
}

//����Ŀ���
void GlWidget::drawExpectRect(QPainter &painter, QPoint center, int radius, QColor color)
{
    int length = radius/6;
    QPoint points[16] = {
                        center+QPoint(-radius, -radius+length), center+QPoint(-radius, -radius), center+QPoint(-radius+length, -radius),
                        center+QPoint( radius, -radius+length), center+QPoint( radius, -radius), center+QPoint( radius-length, -radius),
                        center+QPoint( radius,  radius-length), center+QPoint( radius,  radius), center+QPoint( radius-length,  radius),
                        center+QPoint(-radius,  radius-length), center+QPoint(-radius,  radius), center+QPoint(-radius+length,  radius),
                        center+QPoint(-length, 0), center+QPoint(length, 0),
                        center+QPoint(0, -length), center+QPoint(0, length),
                        };
    painter.setPen(color);
    painter.drawPolyline(points, 3);
    painter.drawPolyline(points+3, 3);
    painter.drawPolyline(points+6, 3);
    painter.drawPolyline(points+9, 3);
    painter.drawPolyline(points+12, 2);
    painter.drawPolyline(points+14, 2);

    m_expectRect = QRect(center - QPoint(radius,radius), center + QPoint(radius,radius));
}

//QImageת������ͼ
void GlWidget::imageConverToTexture(QImage img)
{
    //����������
    glFunctions->glFlush();
    makeCurrent();

    //�������ڳߴ�
    if(this->size() != img.size())
        this->resize(img.size());

    //ת������ͼ
    if(texture_y->isStorageAllocated())  texture_y->destroy();
    texture_y->setData(img, QOpenGLTexture::DontGenerateMipMaps);
    //��λ��ʾ��־
    displayResultReady = false;
    displayFrameReady = false;
    displayQImageReady = true;
}

//����ʾ
void GlWidget::turnOnDisplay()
{
    isDisplayTurnOn = true;
}

//�ر���ʾ
void GlWidget::turnOffDisplay()
{
    isDisplayTurnOn = false;
    update();
}

//��ѯ�Ƿ��Ѿ���ʾͼ��
bool GlWidget::isDisplayAlreadyTurnOn()
{
    return isDisplayTurnOn;
}

//����¼�
void GlWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();

    m_expectCatched = false;
    m_roiLeftCatched = false;
    m_roiRightCatched = false;
    m_roiUpCatched = false;
    m_roiDownCatched = false;

    if(displayResultReady)
    {
        //Ŀ����϶�
        if(m_expectRect.contains(event->pos()))
        {
            m_expectCatched = true;
            this->setCursor(Qt::ClosedHandCursor);
        }
        else
        {
            //��߿�
            if(abs(event->x() - m_roiRect.left()) <= 20)
            {
                m_roiLeftCatched = true;
                this->setCursor(Qt::SizeHorCursor);
            }
            //�ұ߿�
            if(abs(event->x() - m_roiRect.right()) <= 20)
            {
                m_roiRightCatched = true;
                this->setCursor(Qt::SizeHorCursor);
            }
            //�ϱ߿�
            if(abs(event->y() - m_roiRect.top()) <= 20)
            {
                m_roiUpCatched = true;
                this->setCursor(Qt::SizeVerCursor);
            }
            //�±߿�
            if(abs(event->y() - m_roiRect.bottom()) <= 20)
            {
                m_roiDownCatched = true;
                this->setCursor(Qt::SizeVerCursor);
            }
        }
    }
}

//����¼�
void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if(displayResultReady)
        {
            int dx = event->x() - m_roiRect.x();
            int dy = event->y() - m_roiRect.y();
            //Ŀ����϶�
            if(m_expectCatched)
            {
                emit posChanged(0, 0, 0, 0, (qreal)dx*100.0/m_roiRect.width(), (qreal)dy*100.0/m_roiRect.height());
            }
            else
            {
                //��߿�
                if(m_roiLeftCatched)
                     emit posChanged(0, 0, (qreal)event->x()*100.0/width(), 0, 0, 0);
                //�ұ߿�
                if(m_roiRightCatched)
                     emit posChanged(0, 0, 0, (qreal)event->x()*100.0/width(), 0, 0);
                //�ϱ߿�
                if(m_roiUpCatched)
                     emit posChanged((qreal)event->y()*100.0/height(), 0, 0, 0, 0, 0);
                //�±߿�
                if(m_roiDownCatched)
                     emit posChanged(0, (qreal)event->y()*100.0/height(), 0, 0, 0, 0);
            }
        }
    }
}
//����¼�
void GlWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(Qt::ArrowCursor);
}

//���ڹر��¼�
void GlWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit visableChanged(false);
}

//�Ƽ���С�ߴ�
QSize GlWidget::minimumSizeHint() const
{
    return QSize(640, 360);
}

//�Ƽ��ߴ�
QSize GlWidget::sizeHint() const
{
    return QSize(960, 540);
}








//�������룬��ʱ�Ѻó�ʱ���о�������QPainter��OpenGL�����Ⱦ�Ĵ��룬�����������浵���Ժ�ο�
//ע���1.painter.endNativePainting()֮�������Ҫ��QPainter��ͼ�Ļ���Ҫ��relase��relase����unbind��unbind
//2.���ƶ����fbo�л�����Ļ�Ϻ��ӿڻ�ı䣬��Ҫ�ֶ�����һ���ӿ�
//
//
//
//OpenGl���غ�������ͼ
/*void GlWidget::paintGL()
{

    const QRect drawRect(0, 0, 400, 400);
    const QSize drawRectSize = drawRect.size();

    QOpenGLFramebufferObject fbo(drawRectSize, QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo.bind();

    QOpenGLPaintDevice device(drawRectSize);
    QPainter painter;
    painter.begin(&device);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);



    painter.fillRect(drawRect, Qt::blue);

    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::red);
    painter.drawEllipse(0, 100, 400, 200);
    painter.drawEllipse(100, 0, 200, 400);

    painter.beginNativePainting();
    static const float vertexPositions[] = {
            -0.8f, -0.8f, 0.0f,
             0.8f, -0.8f, 0.0f,
             0.0f,  0.8f, 0.0f
        };

        static const float vertexColors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        QOpenGLBuffer vertexPositionBuffer(QOpenGLBuffer::VertexBuffer);
        vertexPositionBuffer.create();
        vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vertexPositionBuffer.bind();
        vertexPositionBuffer.allocate(vertexPositions, 9 * sizeof(float));

        QOpenGLBuffer vertexColorBuffer(QOpenGLBuffer::VertexBuffer);
        vertexColorBuffer.create();
        vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vertexColorBuffer.bind();
        vertexColorBuffer.allocate(vertexColors, 9 * sizeof(float));

        QOpenGLShaderProgram program;
        program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                        "#version 330\n"
                                        "in vec3 position;\n"
                                        "in vec3 color;\n"
                                        "out vec3 fragColor;\n"
                                        "void main() {\n"
                                        "    fragColor = color;\n"
                                        "    gl_Position = vec4(position, 1.0);\n"
                                        "}\n"
                                        );
        program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        "#version 330\n"
                                        "in vec3 fragColor;\n"
                                        "out vec4 color;\n"
                                        "void main() {\n"
                                        "    color = vec4(fragColor, 1.0);\n"
                                        "}\n"
                                        );
        program.link();
        program.bind();

        vertexPositionBuffer.bind();
        program.enableAttributeArray("position");
        program.setAttributeBuffer("position", GL_FLOAT, 0, 3);

        vertexColorBuffer.bind();
        program.enableAttributeArray("color");
        program.setAttributeBuffer("color", GL_FLOAT, 0, 3);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        program.release();
        vertexPositionBuffer.release();
        vertexColorBuffer.release();

    painter.endNativePainting();

    fbo.isBound();
    painter.setPen(QPen(Qt::white, 1.0));
    QFont font;
    font.setPointSize(24);
    painter.setFont(font);
    painter.drawText(drawRect, "QPainter mix", QTextOption(Qt::AlignCenter));
    painter.end();

    //fbo.release();
    GLuint tex_OSD = fbo.takeTexture();
    QOpenGLFramebufferObject::bindDefault();
    //��ʼ�������������VAO��
    if(!m_vao.isCreated()) m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //װ�仺�����VBO��
    static const GLfloat vertices[16] = {
        //vertexVertices��������
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        //textureVertices��������
        0.0f,  0.0f,
        1.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f
    };
    m_vbo.create();                                            //glGenBuffers
    m_vbo.bind();                                              //glBindBuffer
    m_vbo.allocate(vertices, 16 * sizeof(GLfloat));   //blBUfferData

    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_TEXTURE);
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(ATTRIB_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(8 * sizeof(GLfloat)));
    m_vbo.release();

    QOpenGLShaderProgram program1;
    program1.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                     "attribute vec4  vertexIn;\n"
                                     "attribute vec4  textureIn;\n"
                                     "varying vec4    textureCoord;\n"
                                     "void main(void)\n"
                                     "{\n"
                                     "    gl_Position = vertexIn;\n"
                                     "    textureCoord = textureIn;\n"
                                     "}\n"
                                    );
    program1.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     "uniform sampler2D   texture;\n"
                                     "varying vec4        textureCoord;\n"
                                     "void main(void)\n"
                                     "{\n"
                                     "    gl_FragColor = texture2D(texture, textureCoord.st);\n"
                                     "}\n"
                                    );
    program1.bindAttributeLocation("vertexIn", ATTRIB_VERTEX);
    program1.bindAttributeLocation("textureIn", ATTRIB_TEXTURE);
    program1.link();
    program1.bind();


    //����ͼ
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_OSD);

    program1.setUniformValue("texture", 1);

    //�ı��ӿ�
    glViewport(0,0,width(),height());

    //����ͼ��
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program1.release();
    glDeleteTextures(1,&tex_OSD);



}*/




