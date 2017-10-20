#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QHostInfo>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    param_changed(false)
{
    ui->setupUi(this);

    //从文件中读取参数,并写入窗体
    getParamFromFile(QCoreApplication::applicationDirPath()+"/config.ini");
    setParamToUI();

    //成员类初始化
    video_source = new VideoSource(video_source_param, this);
    detector = new Detector(detector_param, this);

    //图像预览子窗口
    widgetColor = new GlWidget;
    widgetGray = new GlWidget;
    widgetBlur = new GlWidget;
    widgetEdge = new GlWidget;
    widgetHough = new GlWidget;
    widgetColor->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    widgetGray->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    widgetBlur->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    widgetEdge->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    widgetHough->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    widgetColor->setAttribute(Qt::WA_QuitOnClose,false);
    widgetGray->setAttribute(Qt::WA_QuitOnClose,false);
    widgetBlur->setAttribute(Qt::WA_QuitOnClose,false);
    widgetEdge->setAttribute(Qt::WA_QuitOnClose,false);
    widgetHough->setAttribute(Qt::WA_QuitOnClose,false);
    widgetColor->setWindowTitle(QString::fromLocal8Bit("预览图像"));
    widgetGray->setWindowTitle(QString::fromLocal8Bit("灰度图"));
    widgetBlur->setWindowTitle(QString::fromLocal8Bit("滤波后的图像"));
    widgetEdge->setWindowTitle(QString::fromLocal8Bit("图像轮廓"));
    widgetHough->setWindowTitle(QString::fromLocal8Bit("Hough累加器"));
    connect(widgetColor, &GlWidget::visableChanged, ui->groupBox_7, &QGroupBox::setChecked);
    connect(widgetGray, &GlWidget::visableChanged, ui->checkBox_GrayImage, &QCheckBox::setChecked);
    connect(widgetBlur, &GlWidget::visableChanged, ui->checkBox_FiltedImage, &QCheckBox::setChecked);
    connect(widgetEdge, &GlWidget::visableChanged, ui->checkBox_EdgeImage, &QCheckBox::setChecked);
    connect(widgetHough, &GlWidget::visableChanged, ui->checkBox_AccImage, &QCheckBox::setChecked);

    //注册自定义类型
    qRegisterMetaType<FrameRawDataStruct>("FrameRawDataStruct");
    qRegisterMetaType<DetectResultStruct>("DetectResultStruct");

    //连接信号和槽
    connectSignals();
}

//析构函数
MainWindow::~MainWindow()
{
    widgetColor->deleteLater();
    delete ui;
    video_source->deleteLater();
    detector->deleteLater();
}

//窗口关闭事件，弹出对话框确认
void MainWindow::closeEvent(QCloseEvent *event)
{
    //如果参数被修改，则弹出保存确认对话框
    if(param_changed)
    {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, QString::fromLocal8Bit("退出程序："),
                                       QString(QString::fromLocal8Bit("是否保存参数?")),
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        switch(button)
        {
        case QMessageBox::Yes:
            {
                //从窗体读取参数，并写入文件中
                getParamFromUI();
                setParamToFile(QCoreApplication::applicationDirPath()+"/config.ini");
                if(video_source->isCaptureVideoStart())
                    video_source->stopCaptureVideo();
                event->accept();  //接受退出信号，程序退出
            }break;
        case QMessageBox::No:
            {
                if(video_source->isCaptureVideoStart())
                    video_source->stopCaptureVideo();
                event->accept();  //接受退出信号，程序退出
            }break;
        default:
            event->ignore();  //忽略退出信号，程序继续运行
        }
    }
    else
    {
        event->accept();  //接受退出信号，程序退出
    }
}

//私有函数，设定参数从结构体中设定到窗体元件
void MainWindow::setParamToUI()
{
    //IPC参数
    ui->lineEdit_IP->setText(video_source_param.IpAddress);
    ui->lineEdit_UserName->setText(video_source_param.UserName);
    ui->lineEdit_PW->setText(video_source_param.Password);
    ui->groupBox_ChannalName->setChecked(video_source_param.channalNameEN);
    ui->lineEdit_ChannalName->setText(video_source_param.channalName);
    ui->lineEdit_ChanNameX->setText(QString::number(video_source_param.channalNameX));
    ui->lineEdit_ChanNameY->setText(QString::number(video_source_param.channalNameY));
    ui->groupBox_DispOSD->setChecked(video_source_param.OSD_EN);
    ui->checkBox_DispWeek->setChecked(video_source_param.OSD_DispWeekEN);
    ui->lineEdit_OSDX->setText(QString::number(video_source_param.OSD_X));
    ui->lineEdit_OSDY->setText(QString::number(video_source_param.OSD_Y));
    ui->comboBox_OSDType->setCurrentIndex(video_source_param.OSD_Type-1);
    ui->comboBox_OSDHourType->setCurrentIndex(video_source_param.OSD_HourOSDType-1);
    ui->comboBox_FontType->setCurrentIndex(video_source_param.OSD_FontSize-1);

    //检测参数
    switch(detector_param.img_resample_size.width())
    {
    case 1920:
        ui->comboBox_DownSampling->setCurrentIndex(1);
        break;
    case 1280:
        ui->comboBox_DownSampling->setCurrentIndex(2);
        break;
    case 960:
        ui->comboBox_DownSampling->setCurrentIndex(3);
        break;
    case 640:
        ui->comboBox_DownSampling->setCurrentIndex(4);
        break;
    case 480:
        ui->comboBox_DownSampling->setCurrentIndex(5);
        break;
    default:
        ui->comboBox_DownSampling->setCurrentIndex(0);
    }
    ui->comboBox_FiltType->setCurrentIndex(detector_param.img_filt_type);
    ui->doubleSpinBox_FiltLevel->setValue(detector_param.img_filt_level);
    ui->doubleSpinBox_hough_DP->setValue(detector_param.hough_dp);
    ui->doubleSpinBox__MinDist->setValue(detector_param.min_dist);
    ui->doubleSpinBox_cannyThreshold_1->setValue(detector_param.canny_threshold1);
    ui->doubleSpinBox_cannyThreshold_2->setValue(detector_param.canny_threshold2);
    ui->doubleSpinBox_accThreshold->setValue(detector_param.acc_threshold);
    ui->doubleSpinBox_MinRadius->setValue(detector_param.radius_min);
    ui->doubleSpinBox_MaxRadius->setValue(detector_param.radius_max);
    ui->doubleSpinBox_maxCentBrightness->setValue(detector_param.brightness_max);
    ui->doubleSpinBox_TimeLimit->setValue(detector_param.detector_timelimit_ms);
    ui->groupBox->setChecked(detector_param.pos_limit_en);
    ui->horizontalSlider_top->setValue(detector_param.pos_limit_top);
    ui->horizontalSlider_bottom->setValue(detector_param.pos_limit_bottom);
    ui->horizontalSlider_left->setValue(detector_param.pos_limit_left);
    ui->horizontalSlider_right->setValue(detector_param.pos_limit_right);
    ui->doubleSpinBox_x_expect->setValue(detector_param.expected_pos_x);
    ui->doubleSpinBox_y_expect->setValue(detector_param.expected_pos_y);
    ui->groupBox_ReaultFilter->setChecked(detector_param.pos_filter_en);
    ui->doubleSpinBox_resultFilter_maxCount->setValue(detector_param.pos_filter_maxCount);
    ui->doubleSpinBox_resultFilter_maxDistance->setValue(detector_param.pos_filter_maxDistance);
}

//私有函数，窗体元件设定参数写入结构体
void MainWindow::getParamFromUI()
{
    //IPC参数
    video_source_param.IpAddress       = ui->lineEdit_IP->text();
    video_source_param.UserName        = ui->lineEdit_UserName->text();
    video_source_param.Password        = ui->lineEdit_PW->text();
    video_source_param.channalNameEN   = ui->groupBox_ChannalName->isChecked();
    video_source_param.channalName     = ui->lineEdit_ChannalName->text();
    video_source_param.channalNameX    = ui->lineEdit_ChanNameX->text().toInt();
    video_source_param.channalNameY    = ui->lineEdit_ChanNameY->text().toInt();
    video_source_param.OSD_EN          = ui->groupBox_DispOSD->isChecked();
    video_source_param.OSD_DispWeekEN  = ui->checkBox_DispWeek->isChecked();
    video_source_param.OSD_X           = ui->lineEdit_OSDX->text().toInt();
    video_source_param.OSD_Y           = ui->lineEdit_OSDY->text().toInt();
    video_source_param.OSD_Type        = ui->comboBox_OSDType->currentIndex()+1;
    video_source_param.OSD_HourOSDType = ui->comboBox_OSDHourType->currentIndex()+1;
    video_source_param.OSD_FontSize    = ui->comboBox_FontType->currentIndex()+1;

    //检测参数
    switch(ui->comboBox_DownSampling->currentIndex())
    {
    case 1:
        detector_param.img_resample_size =  QSize(1920,1080);
        break;
    case 2:
        detector_param.img_resample_size =  QSize(1280,720);
        break;
    case 3:
        detector_param.img_resample_size =  QSize(960,540);
        break;
    case 4:
        detector_param.img_resample_size =  QSize(640,360);
        break;
    case 5:
        detector_param.img_resample_size =  QSize(480,270);
        break;
    default:
        detector_param.img_resample_size =  QSize(0,0);
    }
    detector_param.img_filt_type    = (ParamtersForDetector::ImgFiltType)ui->comboBox_FiltType->currentIndex();
    detector_param.img_filt_level   = ui->doubleSpinBox_FiltLevel->value();
    detector_param.hough_dp         = ui->doubleSpinBox_hough_DP->value();
    detector_param.min_dist         = ui->doubleSpinBox__MinDist->value();
    detector_param.canny_threshold1 = ui->doubleSpinBox_cannyThreshold_1->value();
    detector_param.canny_threshold2 = ui->doubleSpinBox_cannyThreshold_2->value();
    detector_param.acc_threshold    = ui->doubleSpinBox_accThreshold->value();
    detector_param.radius_min       = ui->doubleSpinBox_MinRadius->value();
    detector_param.radius_max       = ui->doubleSpinBox_MaxRadius->value();
    detector_param.pos_filter_en    = ui->groupBox_ReaultFilter->isChecked();
    detector_param.pos_filter_maxCount = ui->doubleSpinBox_resultFilter_maxCount->value();
    detector_param.pos_filter_maxDistance = ui->doubleSpinBox_resultFilter_maxDistance->value();
    detector_param.detector_timelimit_ms  = ui->doubleSpinBox_TimeLimit->value();
    detector_param.brightness_max   = ui->doubleSpinBox_maxCentBrightness->value();
    detector_param.pos_limit_en     = ui->groupBox->isChecked();
    detector_param.pos_limit_left   = ui->horizontalSlider_left->value();
    detector_param.pos_limit_top    = ui->horizontalSlider_top->value();
    detector_param.pos_limit_right  = ui->horizontalSlider_right->value();
    detector_param.pos_limit_bottom = ui->horizontalSlider_bottom->value();
    detector_param.expected_pos_x   = ui->doubleSpinBox_x_expect->value();
    detector_param.expected_pos_y   = ui->doubleSpinBox_y_expect->value();

}

//私有函数，从文件读取参数
void MainWindow::getParamFromFile(const QString &fileName)
{
    //检查文件是否存在
    if(QFile::exists(fileName))
    {
        //读取参数
        QSettings config(fileName,QSettings::IniFormat);

        //IPC参数
        video_source_param.IpAddress       = config.value("LOGIN/IP").toString();
        video_source_param.UserName        = config.value("LOGIN/USER_NAME").toString();
        video_source_param.Password        = config.value("LOGIN/PASSWORD").toString();
        video_source_param.channalNameEN   = config.value("CHANNAL_NAME/DISPLAY").toBool();
        video_source_param.channalName     = config.value("CHANNAL_NAME/NAME").toString();
        video_source_param.channalNameX    = config.value("CHANNAL_NAME/POS_X").toInt();
        video_source_param.channalNameY    = config.value("CHANNAL_NAME/POS_Y").toInt();
        video_source_param.OSD_EN          = config.value("OSD/DISPLAY").toBool();
        video_source_param.OSD_DispWeekEN  = config.value("OSD/DISP_WEEK").toBool();
        video_source_param.OSD_X           = config.value("OSD/POS_X").toInt();
        video_source_param.OSD_Y           = config.value("OSD/POS_Y").toInt();
        video_source_param.OSD_Type        = config.value("OSD/DATE_TYPE").toInt();
        video_source_param.OSD_HourOSDType = config.value("OSD/HOUR_TYPE").toInt();
        video_source_param.OSD_FontSize    = config.value("OSD/FONT_TYPE").toInt();

        //检测参数
        detector_param.img_resample_size       = config.value("DETECTOR/RESAMPLE_SIZE").toSize();
        detector_param.img_filt_type           = (ParamtersForDetector::ImgFiltType)config.value("DETECTOR/FILT_TYPE").toInt();
        detector_param.img_filt_level          = config.value("DETECTOR/FILT_LEVEL").toDouble();
        detector_param.hough_dp                = config.value("DETECTOR/DP").toDouble();
        detector_param.min_dist                = config.value("DETECTOR/MIN_DIST").toDouble();
        detector_param.canny_threshold1        = config.value("DETECTOR/CANNY_THRESHOLD1").toDouble();
        detector_param.canny_threshold2        = config.value("DETECTOR/CANNY_THRESHOLD2").toDouble();
        detector_param.acc_threshold           = config.value("DETECTOR/ACC_THRESHOLD").toDouble();
        detector_param.radius_min              = config.value("DETECTOR/MIN_RADIUS").toDouble();
        detector_param.radius_max              = config.value("DETECTOR/MAX_RADIUS").toDouble();
        detector_param.detector_timelimit_ms   = config.value("DETECTOR/TIME_LIMIT").toDouble();
        detector_param.brightness_max          = config.value("ROI/MAX_CENT_BRIGHTNESS").toDouble();
        detector_param.pos_limit_en            = config.value("ROI/POS_LIMIT_EN").toBool();
        detector_param.pos_limit_left          = config.value("ROI/POS_X_CENTER").toDouble();
        detector_param.pos_limit_top           = config.value("ROI/POS_X_RANGE").toDouble();
        detector_param.pos_limit_right         = config.value("ROI/POS_Y_CENTER").toDouble();
        detector_param.pos_limit_bottom        = config.value("ROI/POS_Y_RANGE").toDouble();
        detector_param.pos_filter_en           = config.value("ROI/POS_FILTER_EN").toBool();
        detector_param.pos_filter_maxCount     = config.value("ROI/POS_FILTER_MAX_COUNT").toDouble();
        detector_param.pos_filter_maxDistance  = config.value("ROI/POS_FILTER_MAX_DISTANCE").toDouble();
        detector_param.expected_pos_x          = config.value("ROI/EXPECTED_POS_X").toDouble();
        detector_param.expected_pos_y          = config.value("ROI/EXPECTED_POS_Y").toDouble();

    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误："),
                             QString::fromLocal8Bit("找不到配置文件：config.ini，将在程序运行目录自动创建。"),
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        //创建文件
        QFile configfile(fileName);
        configfile.open(QIODevice::ReadWrite);
        configfile.close();
    }
}

//私有函数，参数写入文件
void MainWindow::setParamToFile(const QString &fileName)
{
    //检查文件是否存在
    if(QFile::exists(fileName))
    {
        //读取参数
        QSettings config(fileName,QSettings::IniFormat);

        //IPC参数
        config.setValue("LOGIN/IP",video_source_param.IpAddress);
        config.setValue("LOGIN/USER_NAME",video_source_param.UserName);
        config.setValue("LOGIN/PASSWORD",video_source_param.Password);
        config.setValue("CHANNAL_NAME/DISPLAY",video_source_param.channalNameEN);
        config.setValue("CHANNAL_NAME/NAME",video_source_param.channalName);
        config.setValue("CHANNAL_NAME/POS_X",video_source_param.channalNameX);
        config.setValue("CHANNAL_NAME/POS_Y",video_source_param.channalNameY);
        config.setValue("OSD/DISPLAY",video_source_param.OSD_EN);
        config.setValue("OSD/DISP_WEEK",video_source_param.OSD_DispWeekEN);
        config.setValue("OSD/POS_X",video_source_param.OSD_X);
        config.setValue("OSD/POS_Y",video_source_param.OSD_Y);
        config.setValue("OSD/DATE_TYPE",video_source_param.OSD_Type);
        config.setValue("OSD/HOUR_TYPE",video_source_param.OSD_HourOSDType);
        config.setValue("OSD/FONT_TYPE",video_source_param.OSD_FontSize);
        //检测参数
        config.setValue("DETECTOR/RESAMPLE_SIZE",detector_param.img_resample_size);
        config.setValue("DETECTOR/FILT_TYPE",detector_param.img_filt_type);
        config.setValue("DETECTOR/FILT_LEVEL",detector_param.img_filt_level);
        config.setValue("DETECTOR/DP",detector_param.hough_dp);
        config.setValue("DETECTOR/MIN_DIST",detector_param.min_dist);
        config.setValue("DETECTOR/CANNY_THRESHOLD1",detector_param.canny_threshold1);
        config.setValue("DETECTOR/CANNY_THRESHOLD2",detector_param.canny_threshold2);
        config.setValue("DETECTOR/ACC_THRESHOLD",detector_param.acc_threshold);
        config.setValue("DETECTOR/MIN_RADIUS",detector_param.radius_min);
        config.setValue("DETECTOR/MAX_RADIUS",detector_param.radius_max);
        config.setValue("DETECTOR/TIME_LIMIT",detector_param.detector_timelimit_ms);
        config.setValue("ROI/MAX_CENT_BRIGHTNESS",detector_param.brightness_max);
        config.setValue("ROI/POS_FILTER_EN",detector_param.pos_filter_en);
        config.setValue("ROI/POS_FILTER_MAX_COUNT",detector_param.pos_filter_maxCount);
        config.setValue("ROI/POS_FILTER_MAX_DISTANCE",detector_param.pos_filter_maxDistance);
        config.setValue("ROI/POS_LIMIT_EN",detector_param.pos_limit_en);
        config.setValue("ROI/POS_X_CENTER",detector_param.pos_limit_left);
        config.setValue("ROI/POS_X_RANGE",detector_param.pos_limit_top);
        config.setValue("ROI/POS_Y_CENTER",detector_param.pos_limit_right);
        config.setValue("ROI/POS_Y_RANGE",detector_param.pos_limit_bottom);
        config.setValue("ROI/EXPECTED_POS_X",detector_param.expected_pos_x);
        config.setValue("ROI/EXPECTED_POS_Y",detector_param.expected_pos_y);
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("错误："),
                             QString::fromLocal8Bit("找不到配置文件：config.ini，将在程序运行目录自动创建。"),
                             QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
        //创建文件
        QFile configfile(fileName);
        configfile.open(QIODevice::ReadWrite);
        configfile.close();
    }
}

//参数已更改槽函数
void MainWindow::on_ParamChanged()
{
    //置位更改标志
    param_changed = true;
    //更改内部变量
    getParamFromUI();
    detector->setParam(detector_param);
}

//从子窗口传过来的参数更改
void MainWindow::on_posChanged(qreal top, qreal bottom, qreal left, qreal right, qreal exp_x, qreal exp_y)
{
    //窗体内部的参数更改
    if(detector_param.pos_limit_en)
    {
        if(top != 0)
            detector_param.pos_limit_top = top;
        if( bottom != 0)
            detector_param.pos_limit_bottom = bottom;
        if(left != 0)
            detector_param.pos_limit_left = left;
        if(right !=0)
            detector_param.pos_limit_right = right;

    }
    if(exp_x != 0)
        detector_param.expected_pos_x = exp_x;
    if(exp_y != 0)
        detector_param.expected_pos_y = exp_y;
    //更改的参数写入窗体部件
    setParamToUI();
    //置位变更标志
    param_changed = true;
}

//连接mainwindow内部的信号和槽
void MainWindow::connectSignals()
{
    connect(ui->lineEdit_IP, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_UserName, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_PW, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->groupBox_ChannalName, &QGroupBox::toggled, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_ChannalName, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_ChanNameX, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_ChanNameY, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->groupBox_DispOSD, &QGroupBox::toggled, this, &MainWindow::on_ParamChanged);
    connect(ui->checkBox_DispWeek, &QCheckBox::toggled, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_OSDX, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->lineEdit_OSDY, &QLineEdit::textChanged, this, &MainWindow::on_ParamChanged);
    connect(ui->comboBox_OSDType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->comboBox_OSDHourType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->comboBox_FontType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->comboBox_DownSampling, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->comboBox_FiltType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_FiltLevel, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_hough_DP, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox__MinDist, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_cannyThreshold_1, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_cannyThreshold_2, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_accThreshold, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_MinRadius, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_MaxRadius, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_maxCentBrightness, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->groupBox, &QGroupBox::toggled, this, &MainWindow::on_ParamChanged);
    connect(ui->horizontalSlider_bottom, SIGNAL(valueChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->horizontalSlider_left, SIGNAL(valueChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->horizontalSlider_right, SIGNAL(valueChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->horizontalSlider_top, SIGNAL(valueChanged(int)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_x_expect, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_y_expect, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_TimeLimit, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->groupBox_ReaultFilter,  &QGroupBox::toggled, this, &MainWindow::on_ParamChanged);
    connect(ui->doubleSpinBox_resultFilter_maxCount, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
    connect(ui->doubleSpinBox_resultFilter_maxDistance, SIGNAL(valueChanged(double)), this, SLOT(on_ParamChanged()));
}



//预览图像check box
void MainWindow::on_groupBox_7_toggled(bool arg1)
{
    if(arg1)
    {
        //打开预览
        widgetColor->show();
        widgetColor->setFixedSize(960, 540);
        widgetColor->turnOnDisplay();
        video_source->starCaptureVideo();

        if(ui->checkBox_MixedImage->isChecked())
        {
            //叠加显示OSD
            disconnect(video_source, &VideoSource::frameGenerated, widgetColor, &GlWidget::receiveFrame);
            connect(video_source, &VideoSource::frameGenerated, detector, &Detector::receiveFrame);
            connect(detector, &Detector::resultReady, widgetColor, &GlWidget::receiveResult);
            connect(widgetColor, &GlWidget::posChanged, this, &MainWindow::on_posChanged);
        }
        else
        {
            //直接显示图像
            disconnect(video_source, &VideoSource::frameGenerated, detector, &Detector::receiveFrame);
            disconnect(detector, &Detector::resultReady, widgetColor, &GlWidget::receiveResult);
            disconnect(widgetColor, &GlWidget::posChanged, this, &MainWindow::on_posChanged);
            connect(video_source, &VideoSource::frameGenerated,widgetColor, &GlWidget::receiveFrame);
        }
    }
    else
    {
        //关闭预览
        widgetColor->hide();
        widgetColor->turnOffDisplay();
        video_source->stopCaptureVideo();
        disconnect(video_source, &VideoSource::frameGenerated, detector, &Detector::receiveFrame);
        disconnect(detector, &Detector::resultReady, widgetColor, &GlWidget::receiveResult);
        disconnect(video_source, &VideoSource::frameGenerated,widgetColor, &GlWidget::receiveFrame);
        widgetGray->hide();
        widgetGray->turnOffDisplay();
        widgetEdge->hide();
        widgetEdge->turnOffDisplay();
        widgetHough->hide();
        widgetHough->turnOffDisplay();
        widgetBlur->hide();
        widgetBlur->turnOffDisplay();
        ui->checkBox_MixedImage->setChecked(false);
        ui->checkBox_GrayImage->setChecked(false);
        ui->checkBox_FiltedImage->setChecked(false);
        ui->checkBox_EdgeImage->setChecked(false);
        ui->checkBox_AccImage->setChecked(false);
    }
}


//调试信息check box
void MainWindow::on_checkBox_MixedImage_toggled(bool checked)
{
    if(checked)
    {
        //叠加显示OSD
        disconnect(video_source, &VideoSource::frameGenerated, widgetColor, &GlWidget::receiveFrame);
        connect(video_source, &VideoSource::frameGenerated, detector, &Detector::receiveFrame);
        connect(detector, &Detector::resultReady, widgetColor, &GlWidget::receiveResult);
        connect(widgetColor, &GlWidget::posChanged, this, &MainWindow::on_posChanged);
    }
    else
    {
        //直接显示图像
        disconnect(video_source, &VideoSource::frameGenerated, detector, &Detector::receiveFrame);
        disconnect(detector, &Detector::resultReady, widgetColor, &GlWidget::receiveResult);
        disconnect(widgetColor, &GlWidget::posChanged, this, &MainWindow::on_posChanged);
        connect(video_source, &VideoSource::frameGenerated,widgetColor, &GlWidget::receiveFrame);
    }
}

// 显示灰度图复选框check box
void MainWindow::on_checkBox_GrayImage_toggled(bool checked)
{
    if(checked)
    {
        //打开预览
        widgetGray->show();
        widgetGray->resize(320, 240);
        widgetGray->turnOnDisplay();
        //连接信号和槽
        connect(detector, &Detector::resultReady, widgetGray, &GlWidget::receiveGrayscaledImageInResult);
    }
    else
    {
        //关闭预览
        widgetGray->hide();
        widgetGray->turnOffDisplay();
        //断开信号和槽
        disconnect(detector, &Detector::resultReady, widgetGray, &GlWidget::receiveGrayscaledImageInResult);
    }
}

//滤波后图像复选框check box
void MainWindow::on_checkBox_FiltedImage_toggled(bool checked)
{
    if(checked)
    {
        //打开预览
        widgetBlur->show();
        widgetBlur->resize(320, 240);
        widgetBlur->turnOnDisplay();
        //连接信号和槽
        connect(detector, &Detector::resultReady, widgetBlur, &GlWidget::receiveBluredImageInResult);
    }
    else
    {
        //关闭预览
        widgetBlur->hide();
        widgetBlur->turnOffDisplay();
        //断开信号和槽
        disconnect(detector, &Detector::resultReady, widgetBlur, &GlWidget::receiveBluredImageInResult);
    }
}
//轮廓图像复选框check box
void MainWindow::on_checkBox_EdgeImage_toggled(bool checked)
{
    if(checked)
    {
        //打开预览
        widgetEdge->show();
        widgetEdge->resize(320, 240);
        widgetEdge->turnOnDisplay();
        //连接信号和槽
        connect(detector, &Detector::resultReady, widgetEdge, &GlWidget::receiveEdgeImageInResult);
    }
    else
    {
        //关闭预览
        widgetEdge->hide();
        widgetEdge->turnOffDisplay();
        //断开信号和槽
        disconnect(detector, &Detector::resultReady, widgetEdge, &GlWidget::receiveEdgeImageInResult);
    }
}
//hough累加器图像复选框check box
void MainWindow::on_checkBox_AccImage_toggled(bool checked)
{
    if(checked)
    {
        //打开预览
        widgetHough->show();
        widgetHough->resize(320, 240);
        widgetHough->turnOnDisplay();
        //连接信号和槽
        connect(detector, &Detector::resultReady, widgetHough, &GlWidget::receiveHoughImageInResult);
    }
    else
    {
        //关闭预览
        widgetHough->hide();
        widgetHough->turnOffDisplay();
        //断开信号和槽
        disconnect(detector, &Detector::resultReady, widgetHough, &GlWidget::receiveHoughImageInResult);
    }
}
