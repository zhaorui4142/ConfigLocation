//头文件包含区
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

//宏定义区
#define ATTRIB_VERTEX 0
#define ATTRIB_TEXTURE 1
#define ATTRIB_TEXTURE_INTRV 2
#define BUFFER_OFFSET(offset) ((GLvoid *) (reinterpret_cast<void *>(offset)))



//=============================================================================================//
//==============================以下为：GlWidget类的实现==========================================//


//GlWidget类构造函数
GlWidget::GlWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program_frame(0),
      isDisplayTurnOn(false),
      displayFrameReady(false),
      displayResultReady(false),
      displayQImageReady(false),
      fbo(0)
{
    //设置字体
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

//GlWidget类析构函数
GlWidget::~GlWidget()
{
    cleanup();
    delete cpu_usage;
    delete net_flow;
}

//OpenGl重载函数：初始化
void GlWidget::initializeGL()
{
    const int numVertices = 24;
    //对象销毁后释放opengl资源
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GlWidget::cleanup);

    //初始化OpenGL功能
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1.0);

    //设定opengl function指针
    glFunctions = context()->functions();

    //初始化texture
    texture_y         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_u         = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture_v         = new QOpenGLTexture(QOpenGLTexture::Target2D);

    //初始化顶点数组对象（VAO）
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //装配缓存对象（VBO）
    static const GLfloat vertices[numVertices] = {
        //vertexVertices顶点坐标
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        //textureVertices纹理坐标 1
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        1.0f,  0.0f,
        //textureVertices纹理坐标 2
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

    //创建program对象,(创建、指定源码、编译shader)
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

//OpenGl重载函数：绘图
void GlWidget::paintGL()
{
    //清除屏幕背景
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!isDisplayTurnOn) return;
    if(displayFrameReady)
    {
        //绑定vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //绑定program
        program_frame->bind();//相当于glUseProgram
        program_frame->setUniformValue("tex_y", 1);
        program_frame->setUniformValue("tex_u", 2);
        program_frame->setUniformValue("tex_v", 3);

        //绑定贴图
        texture_y->bind(1);
        texture_u->bind(2);
        texture_v->bind(3);

        //绘制图像
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        program_frame->release();
    }
    if(displayResultReady)
    {
        //绑定vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //绑定program
        program_result->bind();//相当于glUseProgram
        program_result->setUniformValue("tex_y", 1);
        program_result->setUniformValue("tex_u", 2);
        program_result->setUniformValue("tex_v", 3);
        program_result->setUniformValue("tex_overlay", 4);

        //绑定贴图
        texture_y->bind(1);
        texture_u->bind(2);
        texture_v->bind(3);
        GLuint tex_OSD = fbo->texture();
        QOpenGLFramebufferObject::bindDefault();
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, tex_OSD);

        //改变视口
        glViewport(0,0,width(),height());

        //绘制图像
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        program_result->release();
    }
    if(displayQImageReady)
    {
        //绑定vao
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

        //绑定program
        program_qimage->bind();//相当于glUseProgram
        program_qimage->setUniformValue("tex_y", 1);

        //绑定贴图
        texture_y->bind(1);

        //绘制图像
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        program_qimage->release();
    }

}

//OpenGl重载函数：改变窗口大小
void GlWidget::resizeGL(int w, int h)
{
/*
    //让图像分辨率为4的整数倍，否则显示时会有毛边
    int w1=w/4;
    int h1=h/4;

    //让图像按照16:9的比例显示，其余位置显示黑底
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //替换顶点数据
    GLfloat x=(GLfloat)(w1*4)/(GLfloat)w;
    GLfloat y=(GLfloat)(h1*4)/(GLfloat)h;

    if(w1*9 > h1*16)    x = (h1*16.0f)/(w1*9.0f);
    else                y = (w1*9.0)/(h1*16.0f);

    displaySize.setWidth(w*x);
    displaySize.setHeight(h*y);

    const GLfloat vertices[8] = {-x, -y,//vertexVertices顶点坐标
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

//私有函数，清除图像
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

//公有槽函数，接收新的图像帧，并将图像数据转换为贴图
void GlWidget::receiveFrame(FrameRawDataStruct frame)
{
    if(isDisplayTurnOn)
    {
        //转换成贴图
        frameConvertToTexture(frame);
        //置位显示标志
        displayResultReady = false;
        displayFrameReady = true;
        displayQImageReady = false;
        //刷新图像
        update();
    }
    else
        return;
}

//接收检测结果并显示
void GlWidget::receiveResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //绘制fbo
        resultPaintToFbo(result);
        //转换成贴图
        frameConvertToTexture(result.rawFrame);
        //置位显示标志
        displayFrameReady = false;
        displayResultReady = true;
        displayQImageReady = false;
        //刷新图像
        update();
    }
    else
        return;
}

//接收检测结果中的灰度图槽函数
void GlWidget::receiveGrayscaledImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //转换成贴图
        imageConverToTexture(result.imgROI);
        //刷新图像
        update();
    }
    else
        return;
}

//接收检测结果中的图槽函数
void GlWidget::receiveBluredImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //转换成贴图
        imageConverToTexture(result.imgBlured);
        //刷新图像
        update();
    }
    else
        return;
}

//接收检测结果中的图槽函数
void GlWidget::receiveEdgeImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //转换成贴图
        imageConverToTexture(result.imgEdges);
        //刷新图像
        update();
    }
    else
        return;
}

//接收检测结果中的图槽函数
void GlWidget::receiveHoughImageInResult(DetectResultStruct result)
{
    if(isDisplayTurnOn)
    {
        //转换成贴图
        imageConverToTexture(result.imgAccum);
        //刷新图像
        update();
    }
    else
        return;
}

//图像帧转换成贴图
void GlWidget::frameConvertToTexture(FrameRawDataStruct &frame)
{
    //计算各个分量的指针
    // yv12数据格式，其中Y分量长度为width * height, U和V分量长度都为width * height / 4
    int nYLen = frame.imgWidth * frame.imgHeigh;
    char* yData = frame.imgData.data();
    char* vData = &yData[nYLen];
    char* uData = &vData[nYLen>>2];
    if(!uData || !vData) return;

    glFunctions->glFlush();
    makeCurrent();
    //生成纹理，绑定纹理，上传纹理数据
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

//检测结果绘制到fbo中
void GlWidget::resultPaintToFbo(DetectResultStruct &result)
{
    //1.切换到当前widget的context
    glFunctions->glFlush();
    makeCurrent();

    //2.准备fbo
    if(fbo == NULL)
        fbo = new QOpenGLFramebufferObject(displaySize, QOpenGLFramebufferObject::CombinedDepthStencil);
    if(fbo->size() != displaySize)
    {
        fbo->release();
        delete fbo;
        fbo = new QOpenGLFramebufferObject(displaySize, QOpenGLFramebufferObject::CombinedDepthStencil);
    }
    fbo->bind();

    //3.清除FBO
    glFunctions->glClearColor(0.0, 0.0, 0.0, 0.0);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //4.开始绘制
    QOpenGLPaintDevice device(fbo->size());
    QPainter painter;
    painter.begin(&device);
    QColor textColor(255, 255, 255, 255);//文字颜色
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);

    //5.绘制检测区域
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

    //6.绘制参数信息
    //6.1图像参数
    QPoint textPoint(10,20);
    painter.setPen(textColor);
    painter.setBrush(QBrush(QColor(64, 64, 64, 128)));
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 102);
    painter.setFont(font_fbo1);
    painter.drawText(8, 16, QString::fromLocal8Bit("图像参数："));
    painter.drawText(8, 32, QString::fromLocal8Bit("原  始：")+QString::number(result.rawFrame.imgWidth)+"x"+QString::number(result.rawFrame.imgHeigh));
    painter.drawText(8, 48, QString::fromLocal8Bit("降采样：")+QString::number(result.resampleSize.width())+"x"+QString::number(result.resampleSize.height()));
    painter.drawText(8, 64, QString::fromLocal8Bit("窗  口：")+QString::number(this->width())+"x"+QString::number(this->height()));
    painter.drawText(8, 80, QString::fromLocal8Bit("ROI   ：")+QString::number(result.imgROI.width())+"x"+QString::number(result.imgROI.height()));
    painter.drawText(8, 96, QString::fromLocal8Bit("帧  率：")+QString::number(result.rawFrame.frameRate)+"fps");
    painter.restore();

    //6.2性能
    textPoint = QPoint(10,140);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 182);
    painter.setFont(font_fbo1);
    painter.drawText(8,  16, QString::fromLocal8Bit("性能："));
    painter.drawText(8,  32, QString::fromLocal8Bit("多线程数：")+QString::number(result.count_used_thread));
    painter.drawText(8,  48, QString::fromLocal8Bit("图像缩放：")+QString::number(result.elapsed_ms_scale, 'f', 2)+"ms");
    painter.drawText(8,  64, QString::fromLocal8Bit("图像滤波：")+QString::number(result.elapsed_ms_blur, 'f', 2)+"ms");
    painter.drawText(8,  80, QString::fromLocal8Bit("计算轮廓：")+QString::number(result.elapsed_ms_canny, 'f', 2)+"ms");
    painter.drawText(8,  96, QString::fromLocal8Bit("直方图  ：")+QString::number(result.elapsed_ms_histogram, 'f', 2)+"ms");
    painter.drawText(8, 112, QString::fromLocal8Bit("霍夫变换：")+QString::number(result.elapsed_ms_accum, 'f', 2)+"ms");
    painter.drawText(8, 128, QString::fromLocal8Bit("查找圆心：")+QString::number(result.elapsed_ms_findPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 144, QString::fromLocal8Bit("结果排序：")+QString::number(result.elapsed_ms_sortPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 160, QString::fromLocal8Bit("结果筛选：")+QString::number(result.elapsed_ms_checkPossibleCenter, 'f', 2)+"ms");
    painter.drawText(8, 176, QString::fromLocal8Bit("总耗时  ：")+QString::number(result.elapsed_ms_total, 'f', 2)+"ms");
    painter.restore();

    //6.3检测结果
    textPoint = QPoint(10,340);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 136, 166);
    painter.setFont(font_fbo1);
    painter.drawText(0, 16, QString::fromLocal8Bit("目标检测："));
    painter.drawText(4,  32, QString::fromLocal8Bit("边缘像素点数：")+QString::number(result.count_nz));
    painter.drawText(4,  48, QString::fromLocal8Bit("可能的目标数：")+QString::number(result.count_possible_center));
    painter.drawText(4,  64, QString::fromLocal8Bit("筛选后目标数：")+QString::number(result.satisfiedCycles.size()));
    if(result.satisfiedCycles.size() !=0 )
    {
        cycleInfo &best = result.satisfiedCycles[result.theBestCycleIndex];
        painter.drawText(4,  80, QString::fromLocal8Bit("最优圆心坐标：X")+QString::number(best.centerPoint.x(), 'f', 0));
        painter.drawText(4,  96, QString::fromLocal8Bit("最优圆心坐标：Y")+QString::number(best.centerPoint.y(), 'f', 0));
        painter.drawText(4, 112, QString::fromLocal8Bit("最优圆半径  ：")+QString::number(best.radius, 'f', 2));
        painter.drawText(4, 128, QString::fromLocal8Bit("最优圆心亮度：")+QString::number(best.brightness));
        painter.drawText(4, 144, QString::fromLocal8Bit("最优圆hough ：")+QString::number(best.accumCount));
        painter.drawText(4, 158, QString::fromLocal8Bit("最优圆完整度：")+QString::number(best.accumIntensity, 'f', 2));
    }
    else
    {
        painter.drawText(4,  80, QString::fromLocal8Bit("最优圆心坐标：X"));
        painter.drawText(4,  96, QString::fromLocal8Bit("最优圆心坐标：Y"));
        painter.drawText(4, 112, QString::fromLocal8Bit("最优圆半径  ："));
        painter.drawText(4, 128, QString::fromLocal8Bit("最优圆心亮度："));
        painter.drawText(4, 144, QString::fromLocal8Bit("最优圆hough ："));
        painter.drawText(4, 158, QString::fromLocal8Bit("最优圆完整度："));
    }
    painter.restore();

    //6.4CPU使用率
    textPoint = QPoint(800,84);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 128, 88+68*((cpu_usage->GetNumberProcessors()/4)-1));
    painter.setFont(font_fbo1);
    painter.drawText(4, 16, QString::fromLocal8Bit("CPU："));
    for(int i=0; i<cpu_usage->GetNumberProcessors(); i++)
    {
        painter.drawText(4, 16*(i+2), "CPU"+QString::number(i)+":"+QString::number(cpu_usage->GetUseage(i))+"%");
    }
    painter.restore();

    //6.5网络吞吐量
    textPoint = QPoint(800,20);
    painter.save();
    painter.translate(textPoint);
    painter.drawRect(0, 0, 128, 54);
    painter.setFont(font_fbo1);
    painter.drawText(4, 16, QString::fromLocal8Bit("网络："));
    painter.drawText(4, 32,QString::fromLocal8Bit("上传:") + QString::number(net_flow->getUploadingSpeed())+"kbps");
    painter.drawText(4, 48,QString::fromLocal8Bit("下载:") + QString::number(net_flow->getDownloadingSpeed())+"kbps");
    painter.restore();

    //6.6直方图
    textPoint = QPoint(800,460);
    painter.save();
    painter.translate(textPoint);
    QImage histImg = result.imgHistogram;
    if(!histImg.isNull())
    {
        painter.setPen(QColor(255,255,255,255));
        painter.drawRect(0, 0, histImg.width()/2, histImg.height()/2);
        painter.setFont(font_fbo_title);
        painter.drawText(0, -4, QString::fromLocal8Bit("直方图："));
        painter.drawImage(0, 0, histImg.scaled(128,64));
    }
    painter.restore();

    //7.绘制检测结果
    //7.1绘制检测到的圆
    for(uint i=0; i<result.satisfiedCycles.size(); i++)
    {
        cycleInfo cycle = result.satisfiedCycles[i];
        cycle.centerPoint = QPoint(cycle.centerPoint.x()*width()/result.rawFrame.imgWidth, cycle.centerPoint.y()*height()/result.rawFrame.imgHeigh);
        if(i == result.theBestCycleIndex)
            drawCycleInfo(painter, cycle, QColor(0, 255, 0, 255));
        else
            drawCycleInfo(painter, cycle, QColor(255, 0, 0, 255));
    }

    //7.2绘制目标位置
    QPoint ExceptCenter;
    ExceptCenter.setX(result.expectCenterPoint.x()*this->width()/result.rawFrame.imgWidth);
    ExceptCenter.setY(result.expectCenterPoint.y()*this->height()/result.rawFrame.imgHeigh);
    drawExpectRect(painter, ExceptCenter, result.radius_max, QColor(0, 255, 0, 255));

    //7.7绘制连接线
    //painter.drawLine(QPoint(200,200),ExceptCenter);


    //8.绘制结束
    painter.end();

}

//绘制检测到的圆
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

//绘制目标框
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

//QImage转换成贴图
void GlWidget::imageConverToTexture(QImage img)
{
    //设置上下文
    glFunctions->glFlush();
    makeCurrent();

    //调整窗口尺寸
    if(this->size() != img.size())
        this->resize(img.size());

    //转换成贴图
    if(texture_y->isStorageAllocated())  texture_y->destroy();
    texture_y->setData(img, QOpenGLTexture::DontGenerateMipMaps);
    //置位显示标志
    displayResultReady = false;
    displayFrameReady = false;
    displayQImageReady = true;
}

//打开显示
void GlWidget::turnOnDisplay()
{
    isDisplayTurnOn = true;
}

//关闭显示
void GlWidget::turnOffDisplay()
{
    isDisplayTurnOn = false;
    update();
}

//查询是否已经显示图像
bool GlWidget::isDisplayAlreadyTurnOn()
{
    return isDisplayTurnOn;
}

//鼠标事件
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
        //目标框被拖动
        if(m_expectRect.contains(event->pos()))
        {
            m_expectCatched = true;
            this->setCursor(Qt::ClosedHandCursor);
        }
        else
        {
            //左边框
            if(abs(event->x() - m_roiRect.left()) <= 20)
            {
                m_roiLeftCatched = true;
                this->setCursor(Qt::SizeHorCursor);
            }
            //右边框
            if(abs(event->x() - m_roiRect.right()) <= 20)
            {
                m_roiRightCatched = true;
                this->setCursor(Qt::SizeHorCursor);
            }
            //上边框
            if(abs(event->y() - m_roiRect.top()) <= 20)
            {
                m_roiUpCatched = true;
                this->setCursor(Qt::SizeVerCursor);
            }
            //下边框
            if(abs(event->y() - m_roiRect.bottom()) <= 20)
            {
                m_roiDownCatched = true;
                this->setCursor(Qt::SizeVerCursor);
            }
        }
    }
}

//鼠标事件
void GlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if(displayResultReady)
        {
            int dx = event->x() - m_roiRect.x();
            int dy = event->y() - m_roiRect.y();
            //目标框被拖动
            if(m_expectCatched)
            {
                emit posChanged(0, 0, 0, 0, (qreal)dx*100.0/m_roiRect.width(), (qreal)dy*100.0/m_roiRect.height());
            }
            else
            {
                //左边框
                if(m_roiLeftCatched)
                     emit posChanged(0, 0, (qreal)event->x()*100.0/width(), 0, 0, 0);
                //右边框
                if(m_roiRightCatched)
                     emit posChanged(0, 0, 0, (qreal)event->x()*100.0/width(), 0, 0);
                //上边框
                if(m_roiUpCatched)
                     emit posChanged((qreal)event->y()*100.0/height(), 0, 0, 0, 0, 0);
                //下边框
                if(m_roiDownCatched)
                     emit posChanged(0, (qreal)event->y()*100.0/height(), 0, 0, 0, 0);
            }
        }
    }
}
//鼠标事件
void GlWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(Qt::ArrowCursor);
}

//窗口关闭事件
void GlWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit visableChanged(false);
}

//推荐最小尺寸
QSize GlWidget::minimumSizeHint() const
{
    return QSize(640, 360);
}

//推荐尺寸
QSize GlWidget::sizeHint() const
{
    return QSize(960, 540);
}








//废弃代码，当时费好长时间研究出来的QPainter和OpenGL混合渲染的代码，运行正常，存档供以后参考
//注意点1.painter.endNativePainting()之后如果还要用QPainter绘图的话需要该relase的relase，该unbind的unbind
//2.绘制对象从fbo切换到屏幕上后，视口会改变，需要手动设置一下视口
//
//
//
//OpenGl重载函数：绘图
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
    //初始化顶点数组对象（VAO）
    if(!m_vao.isCreated()) m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    //装配缓存对象（VBO）
    static const GLfloat vertices[16] = {
        //vertexVertices顶点坐标
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
        //textureVertices纹理坐标
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


    //绑定贴图
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex_OSD);

    program1.setUniformValue("texture", 1);

    //改变视口
    glViewport(0,0,width(),height());

    //绘制图像
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    program1.release();
    glDeleteTextures(1,&tex_OSD);



}*/




