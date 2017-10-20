/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_11;
    QTabWidget *tabWidget;
    QWidget *tab_0;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QLineEdit *lineEdit_PW;
    QLabel *label_31;
    QLineEdit *lineEdit_UserName;
    QLabel *label_32;
    QLineEdit *lineEdit_IP;
    QLabel *label_30;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *groupBox_DispOSD;
    QGridLayout *gridLayout_4;
    QLabel *label_37;
    QSpacerItem *verticalSpacer_4;
    QComboBox *comboBox_OSDHourType;
    QLineEdit *lineEdit_OSDY;
    QCheckBox *checkBox_DispWeek;
    QLineEdit *lineEdit_OSDX;
    QLabel *label_35;
    QLabel *label_40;
    QLabel *label_33;
    QComboBox *comboBox_FontType;
    QLabel *label_36;
    QLabel *label;
    QComboBox *comboBox_OSDType;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_ChannalName;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_41;
    QLineEdit *lineEdit_ChanNameX;
    QLineEdit *lineEdit_ChannalName;
    QLabel *label_42;
    QLabel *label_34;
    QLineEdit *lineEdit_ChanNameY;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tab_1;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QCheckBox *checkBox_MixedImage;
    QCheckBox *checkBox_GrayImage;
    QCheckBox *checkBox_FiltedImage;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *checkBox_EdgeImage;
    QCheckBox *checkBox_AccImage;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QLabel *label_45;
    QSpacerItem *verticalSpacer_3;
    QComboBox *comboBox_DownSampling;
    QLabel *label_43;
    QLabel *label_44;
    QComboBox *comboBox_FiltType;
    QLabel *label_23;
    QLabel *label_17;
    QLabel *label_25;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBox_FiltLevel;
    QDoubleSpinBox *doubleSpinBox_cannyThreshold_1;
    QDoubleSpinBox *doubleSpinBox_cannyThreshold_2;
    QDoubleSpinBox *doubleSpinBox_accThreshold;
    QDoubleSpinBox *doubleSpinBox_hough_DP;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_14;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_TimeLimit;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_5;
    QLabel *label_56;
    QDoubleSpinBox *doubleSpinBox_x_expect;
    QLabel *label_26;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_55;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox_y_expect;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_ReaultFilter;
    QGridLayout *gridLayout_15;
    QDoubleSpinBox *doubleSpinBox_resultFilter_maxCount;
    QLabel *label_28;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_58;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_resultFilter_maxDistance;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_10;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_12;
    QLabel *label_48;
    QLabel *label_27;
    QSlider *horizontalSlider_left;
    QSlider *horizontalSlider_right;
    QSlider *horizontalSlider_top;
    QLabel *label_29;
    QSlider *horizontalSlider_bottom;
    QLabel *label_60;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_39;
    QLabel *label_46;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_24;
    QLabel *label_38;
    QDoubleSpinBox *doubleSpinBox_maxCentBrightness;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBox_MinRadius;
    QLabel *label_22;
    QDoubleSpinBox *doubleSpinBox_MaxRadius;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox__MinDist;
    QLabel *label_5;
    QWidget *tab_4;
    QGridLayout *gridLayout_13;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_exit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(456, 342);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(456, 342));
        MainWindow->setMaximumSize(QSize(456, 342));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_11 = new QGridLayout(centralWidget);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(true);
        tab_0 = new QWidget();
        tab_0->setObjectName(QStringLiteral("tab_0"));
        gridLayout_7 = new QGridLayout(tab_0);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        groupBox_3 = new QGroupBox(tab_0);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        groupBox_3->setLayoutDirection(Qt::LeftToRight);
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        lineEdit_PW = new QLineEdit(groupBox_3);
        lineEdit_PW->setObjectName(QStringLiteral("lineEdit_PW"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_PW->sizePolicy().hasHeightForWidth());
        lineEdit_PW->setSizePolicy(sizePolicy2);
        lineEdit_PW->setMinimumSize(QSize(60, 20));
        lineEdit_PW->setMaximumSize(QSize(100, 16777215));

        gridLayout_9->addWidget(lineEdit_PW, 2, 1, 1, 1);

        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_9->addWidget(label_31, 1, 0, 1, 1);

        lineEdit_UserName = new QLineEdit(groupBox_3);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        lineEdit_UserName->setMinimumSize(QSize(60, 20));
        lineEdit_UserName->setMaximumSize(QSize(100, 16777215));

        gridLayout_9->addWidget(lineEdit_UserName, 1, 1, 1, 1);

        label_32 = new QLabel(groupBox_3);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_9->addWidget(label_32, 2, 0, 1, 1);

        lineEdit_IP = new QLineEdit(groupBox_3);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setMinimumSize(QSize(100, 20));
        lineEdit_IP->setMaximumSize(QSize(100, 16777215));

        gridLayout_9->addWidget(lineEdit_IP, 0, 1, 1, 1);

        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setLayoutDirection(Qt::LeftToRight);

        gridLayout_9->addWidget(label_30, 0, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_9->addItem(verticalSpacer_6, 3, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox_DispOSD = new QGroupBox(tab_0);
        groupBox_DispOSD->setObjectName(QStringLiteral("groupBox_DispOSD"));
        groupBox_DispOSD->setLayoutDirection(Qt::LeftToRight);
        groupBox_DispOSD->setFlat(false);
        groupBox_DispOSD->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupBox_DispOSD);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_37 = new QLabel(groupBox_DispOSD);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_4->addWidget(label_37, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 8, 1, 1, 1);

        comboBox_OSDHourType = new QComboBox(groupBox_DispOSD);
        comboBox_OSDHourType->setObjectName(QStringLiteral("comboBox_OSDHourType"));
        comboBox_OSDHourType->setMinimumSize(QSize(130, 0));

        gridLayout_4->addWidget(comboBox_OSDHourType, 3, 1, 1, 1);

        lineEdit_OSDY = new QLineEdit(groupBox_DispOSD);
        lineEdit_OSDY->setObjectName(QStringLiteral("lineEdit_OSDY"));
        lineEdit_OSDY->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(lineEdit_OSDY, 1, 1, 1, 1);

        checkBox_DispWeek = new QCheckBox(groupBox_DispOSD);
        checkBox_DispWeek->setObjectName(QStringLiteral("checkBox_DispWeek"));
        checkBox_DispWeek->setAcceptDrops(false);
        checkBox_DispWeek->setLayoutDirection(Qt::LeftToRight);
        checkBox_DispWeek->setChecked(false);
        checkBox_DispWeek->setTristate(false);

        gridLayout_4->addWidget(checkBox_DispWeek, 7, 1, 1, 1);

        lineEdit_OSDX = new QLineEdit(groupBox_DispOSD);
        lineEdit_OSDX->setObjectName(QStringLiteral("lineEdit_OSDX"));
        lineEdit_OSDX->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(lineEdit_OSDX, 0, 1, 1, 1);

        label_35 = new QLabel(groupBox_DispOSD);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_4->addWidget(label_35, 0, 0, 1, 1);

        label_40 = new QLabel(groupBox_DispOSD);
        label_40->setObjectName(QStringLiteral("label_40"));

        gridLayout_4->addWidget(label_40, 4, 0, 1, 1);

        label_33 = new QLabel(groupBox_DispOSD);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_4->addWidget(label_33, 3, 0, 1, 1);

        comboBox_FontType = new QComboBox(groupBox_DispOSD);
        comboBox_FontType->setObjectName(QStringLiteral("comboBox_FontType"));
        comboBox_FontType->setMinimumSize(QSize(130, 0));

        gridLayout_4->addWidget(comboBox_FontType, 4, 1, 1, 1);

        label_36 = new QLabel(groupBox_DispOSD);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_4->addWidget(label_36, 6, 0, 1, 1);

        label = new QLabel(groupBox_DispOSD);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 7, 0, 1, 1);

        comboBox_OSDType = new QComboBox(groupBox_DispOSD);
        comboBox_OSDType->setObjectName(QStringLiteral("comboBox_OSDType"));
        comboBox_OSDType->setMinimumSize(QSize(130, 0));

        gridLayout_4->addWidget(comboBox_OSDType, 6, 1, 1, 1);


        gridLayout_7->addWidget(groupBox_DispOSD, 0, 3, 2, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 1, 0, 1, 1);

        groupBox_ChannalName = new QGroupBox(tab_0);
        groupBox_ChannalName->setObjectName(QStringLiteral("groupBox_ChannalName"));
        groupBox_ChannalName->setCheckable(true);
        groupBox_ChannalName->setChecked(true);
        gridLayout_6 = new QGridLayout(groupBox_ChannalName);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_8, 3, 1, 1, 1);

        label_41 = new QLabel(groupBox_ChannalName);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(label_41, 2, 0, 1, 1);

        lineEdit_ChanNameX = new QLineEdit(groupBox_ChannalName);
        lineEdit_ChanNameX->setObjectName(QStringLiteral("lineEdit_ChanNameX"));
        lineEdit_ChanNameX->setMaximumSize(QSize(100, 16777215));

        gridLayout_6->addWidget(lineEdit_ChanNameX, 1, 1, 1, 2);

        lineEdit_ChannalName = new QLineEdit(groupBox_ChannalName);
        lineEdit_ChannalName->setObjectName(QStringLiteral("lineEdit_ChannalName"));
        lineEdit_ChannalName->setEnabled(true);
        lineEdit_ChannalName->setMinimumSize(QSize(100, 0));
        lineEdit_ChannalName->setMaximumSize(QSize(100, 16777215));

        gridLayout_6->addWidget(lineEdit_ChannalName, 0, 1, 1, 2);

        label_42 = new QLabel(groupBox_ChannalName);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(label_42, 0, 0, 1, 1);

        label_34 = new QLabel(groupBox_ChannalName);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setLayoutDirection(Qt::RightToLeft);

        gridLayout_6->addWidget(label_34, 1, 0, 1, 1);

        lineEdit_ChanNameY = new QLineEdit(groupBox_ChannalName);
        lineEdit_ChanNameY->setObjectName(QStringLiteral("lineEdit_ChanNameY"));
        lineEdit_ChanNameY->setMaximumSize(QSize(100, 16777215));

        gridLayout_6->addWidget(lineEdit_ChanNameY, 2, 1, 1, 2);


        gridLayout_7->addWidget(groupBox_ChannalName, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 1, 4, 1, 1);

        tabWidget->addTab(tab_0, QString());
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        gridLayout_10 = new QGridLayout(tab_1);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_7 = new QGroupBox(tab_1);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setCheckable(true);
        groupBox_7->setChecked(false);
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        checkBox_MixedImage = new QCheckBox(groupBox_7);
        checkBox_MixedImage->setObjectName(QStringLiteral("checkBox_MixedImage"));

        gridLayout_8->addWidget(checkBox_MixedImage, 0, 1, 1, 1);

        checkBox_GrayImage = new QCheckBox(groupBox_7);
        checkBox_GrayImage->setObjectName(QStringLiteral("checkBox_GrayImage"));
        checkBox_GrayImage->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(checkBox_GrayImage, 1, 1, 1, 1);

        checkBox_FiltedImage = new QCheckBox(groupBox_7);
        checkBox_FiltedImage->setObjectName(QStringLiteral("checkBox_FiltedImage"));
        checkBox_FiltedImage->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(checkBox_FiltedImage, 2, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_10, 3, 2, 1, 1);

        checkBox_EdgeImage = new QCheckBox(groupBox_7);
        checkBox_EdgeImage->setObjectName(QStringLiteral("checkBox_EdgeImage"));
        checkBox_EdgeImage->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(checkBox_EdgeImage, 3, 1, 1, 1);

        checkBox_AccImage = new QCheckBox(groupBox_7);
        checkBox_AccImage->setObjectName(QStringLiteral("checkBox_AccImage"));
        checkBox_AccImage->setLayoutDirection(Qt::LeftToRight);

        gridLayout_8->addWidget(checkBox_AccImage, 4, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_7, 0, 2, 1, 2);

        groupBox_4 = new QGroupBox(tab_1);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_45 = new QLabel(groupBox_4);
        label_45->setObjectName(QStringLiteral("label_45"));

        gridLayout->addWidget(label_45, 2, 0, 1, 1, Qt::AlignLeft);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 7, 0, 1, 1);

        comboBox_DownSampling = new QComboBox(groupBox_4);
        comboBox_DownSampling->setObjectName(QStringLiteral("comboBox_DownSampling"));
        comboBox_DownSampling->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(comboBox_DownSampling, 0, 1, 1, 2);

        label_43 = new QLabel(groupBox_4);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_43, 0, 0, 1, 1, Qt::AlignLeft);

        label_44 = new QLabel(groupBox_4);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_44, 1, 0, 1, 1, Qt::AlignLeft);

        comboBox_FiltType = new QComboBox(groupBox_4);
        comboBox_FiltType->setObjectName(QStringLiteral("comboBox_FiltType"));

        gridLayout->addWidget(comboBox_FiltType, 1, 1, 1, 2);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout->addWidget(label_23, 3, 0, 1, 1, Qt::AlignLeft);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 4, 0, 1, 1, Qt::AlignLeft);

        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout->addWidget(label_25, 5, 0, 1, 1, Qt::AlignLeft);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 6, 0, 1, 1, Qt::AlignLeft);

        doubleSpinBox_FiltLevel = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_FiltLevel->setObjectName(QStringLiteral("doubleSpinBox_FiltLevel"));
        doubleSpinBox_FiltLevel->setDecimals(0);
        doubleSpinBox_FiltLevel->setMinimum(3);
        doubleSpinBox_FiltLevel->setMaximum(30);

        gridLayout->addWidget(doubleSpinBox_FiltLevel, 2, 1, 1, 2);

        doubleSpinBox_cannyThreshold_1 = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_cannyThreshold_1->setObjectName(QStringLiteral("doubleSpinBox_cannyThreshold_1"));
        doubleSpinBox_cannyThreshold_1->setDecimals(0);
        doubleSpinBox_cannyThreshold_1->setMinimum(0);
        doubleSpinBox_cannyThreshold_1->setMaximum(65536);
        doubleSpinBox_cannyThreshold_1->setSingleStep(1);

        gridLayout->addWidget(doubleSpinBox_cannyThreshold_1, 3, 1, 1, 2);

        doubleSpinBox_cannyThreshold_2 = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_cannyThreshold_2->setObjectName(QStringLiteral("doubleSpinBox_cannyThreshold_2"));
        doubleSpinBox_cannyThreshold_2->setDecimals(0);
        doubleSpinBox_cannyThreshold_2->setMinimum(0);
        doubleSpinBox_cannyThreshold_2->setMaximum(65536);

        gridLayout->addWidget(doubleSpinBox_cannyThreshold_2, 4, 1, 1, 2);

        doubleSpinBox_accThreshold = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_accThreshold->setObjectName(QStringLiteral("doubleSpinBox_accThreshold"));
        doubleSpinBox_accThreshold->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        doubleSpinBox_accThreshold->setDecimals(0);
        doubleSpinBox_accThreshold->setMinimum(0);
        doubleSpinBox_accThreshold->setMaximum(56636);
        doubleSpinBox_accThreshold->setSingleStep(1);

        gridLayout->addWidget(doubleSpinBox_accThreshold, 5, 1, 1, 2);

        doubleSpinBox_hough_DP = new QDoubleSpinBox(groupBox_4);
        doubleSpinBox_hough_DP->setObjectName(QStringLiteral("doubleSpinBox_hough_DP"));
        doubleSpinBox_hough_DP->setMinimum(1);
        doubleSpinBox_hough_DP->setMaximum(10);
        doubleSpinBox_hough_DP->setSingleStep(0.5);

        gridLayout->addWidget(doubleSpinBox_hough_DP, 6, 1, 1, 2);


        gridLayout_10->addWidget(groupBox_4, 0, 0, 3, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_9, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_5, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab_1);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_14 = new QGridLayout(groupBox_2);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_14->addWidget(label_2, 0, 0, 1, 1);

        doubleSpinBox_TimeLimit = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_TimeLimit->setObjectName(QStringLiteral("doubleSpinBox_TimeLimit"));
        doubleSpinBox_TimeLimit->setDecimals(0);
        doubleSpinBox_TimeLimit->setMinimum(5);
        doubleSpinBox_TimeLimit->setMaximum(5000);

        gridLayout_14->addWidget(doubleSpinBox_TimeLimit, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_14->addWidget(label_3, 0, 2, 1, 1);


        gridLayout_10->addWidget(groupBox_2, 1, 2, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer, 2, 2, 2, 1);

        tabWidget->addTab(tab_1, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_5 = new QGridLayout(groupBox_9);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_56 = new QLabel(groupBox_9);
        label_56->setObjectName(QStringLiteral("label_56"));

        gridLayout_5->addWidget(label_56, 0, 2, 1, 1);

        doubleSpinBox_x_expect = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_x_expect->setObjectName(QStringLiteral("doubleSpinBox_x_expect"));

        gridLayout_5->addWidget(doubleSpinBox_x_expect, 0, 1, 1, 1);

        label_26 = new QLabel(groupBox_9);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_5->addWidget(label_26, 0, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_7, 2, 1, 1, 1);

        label_55 = new QLabel(groupBox_9);
        label_55->setObjectName(QStringLiteral("label_55"));

        gridLayout_5->addWidget(label_55, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_9);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 1, 0, 1, 1);

        doubleSpinBox_y_expect = new QDoubleSpinBox(groupBox_9);
        doubleSpinBox_y_expect->setObjectName(QStringLiteral("doubleSpinBox_y_expect"));

        gridLayout_5->addWidget(doubleSpinBox_y_expect, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_7, 0, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_9, 0, 2, 1, 1);

        groupBox_ReaultFilter = new QGroupBox(tab);
        groupBox_ReaultFilter->setObjectName(QStringLiteral("groupBox_ReaultFilter"));
        groupBox_ReaultFilter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_ReaultFilter->setCheckable(true);
        groupBox_ReaultFilter->setChecked(false);
        gridLayout_15 = new QGridLayout(groupBox_ReaultFilter);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        doubleSpinBox_resultFilter_maxCount = new QDoubleSpinBox(groupBox_ReaultFilter);
        doubleSpinBox_resultFilter_maxCount->setObjectName(QStringLiteral("doubleSpinBox_resultFilter_maxCount"));
        doubleSpinBox_resultFilter_maxCount->setDecimals(0);
        doubleSpinBox_resultFilter_maxCount->setMinimum(1);
        doubleSpinBox_resultFilter_maxCount->setMaximum(9999);

        gridLayout_15->addWidget(doubleSpinBox_resultFilter_maxCount, 0, 1, 1, 1);

        label_28 = new QLabel(groupBox_ReaultFilter);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_15->addWidget(label_28, 0, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_9, 2, 1, 1, 1);

        label_58 = new QLabel(groupBox_ReaultFilter);
        label_58->setObjectName(QStringLiteral("label_58"));

        gridLayout_15->addWidget(label_58, 1, 2, 1, 1);

        label_11 = new QLabel(groupBox_ReaultFilter);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_15->addWidget(label_11, 1, 0, 1, 1);

        doubleSpinBox_resultFilter_maxDistance = new QDoubleSpinBox(groupBox_ReaultFilter);
        doubleSpinBox_resultFilter_maxDistance->setObjectName(QStringLiteral("doubleSpinBox_resultFilter_maxDistance"));
        doubleSpinBox_resultFilter_maxDistance->setDecimals(1);
        doubleSpinBox_resultFilter_maxDistance->setMinimum(1);
        doubleSpinBox_resultFilter_maxDistance->setMaximum(9999);

        gridLayout_15->addWidget(doubleSpinBox_resultFilter_maxDistance, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_8, 0, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_ReaultFilter, 1, 1, 1, 2);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_10, 3, 0, 1, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setCheckable(true);
        gridLayout_12 = new QGridLayout(groupBox);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        label_48 = new QLabel(groupBox);
        label_48->setObjectName(QStringLiteral("label_48"));

        gridLayout_12->addWidget(label_48, 1, 2, 1, 1);

        label_27 = new QLabel(groupBox);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_12->addWidget(label_27, 1, 0, 1, 1);

        horizontalSlider_left = new QSlider(groupBox);
        horizontalSlider_left->setObjectName(QStringLiteral("horizontalSlider_left"));
        horizontalSlider_left->setOrientation(Qt::Horizontal);
        horizontalSlider_left->setInvertedAppearance(false);

        gridLayout_12->addWidget(horizontalSlider_left, 1, 1, 1, 1);

        horizontalSlider_right = new QSlider(groupBox);
        horizontalSlider_right->setObjectName(QStringLiteral("horizontalSlider_right"));
        horizontalSlider_right->setValue(99);
        horizontalSlider_right->setOrientation(Qt::Horizontal);
        horizontalSlider_right->setInvertedAppearance(false);

        gridLayout_12->addWidget(horizontalSlider_right, 1, 3, 1, 1);

        horizontalSlider_top = new QSlider(groupBox);
        horizontalSlider_top->setObjectName(QStringLiteral("horizontalSlider_top"));
        horizontalSlider_top->setSliderPosition(0);
        horizontalSlider_top->setTracking(true);
        horizontalSlider_top->setOrientation(Qt::Horizontal);
        horizontalSlider_top->setInvertedAppearance(false);
        horizontalSlider_top->setInvertedControls(false);

        gridLayout_12->addWidget(horizontalSlider_top, 0, 1, 1, 1);

        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_12->addWidget(label_29, 0, 0, 1, 1);

        horizontalSlider_bottom = new QSlider(groupBox);
        horizontalSlider_bottom->setObjectName(QStringLiteral("horizontalSlider_bottom"));
        horizontalSlider_bottom->setValue(99);
        horizontalSlider_bottom->setOrientation(Qt::Horizontal);
        horizontalSlider_bottom->setInvertedAppearance(false);

        gridLayout_12->addWidget(horizontalSlider_bottom, 0, 3, 1, 1);

        label_60 = new QLabel(groupBox);
        label_60->setObjectName(QStringLiteral("label_60"));

        gridLayout_12->addWidget(label_60, 0, 2, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 3);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setFlat(false);
        gridLayout_3 = new QGridLayout(groupBox_6);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 3, 4, 1, 1);

        label_39 = new QLabel(groupBox_6);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_3->addWidget(label_39, 3, 3, 1, 1);

        label_46 = new QLabel(groupBox_6);
        label_46->setObjectName(QStringLiteral("label_46"));

        gridLayout_3->addWidget(label_46, 2, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 4, 0, 1, 1);

        label_24 = new QLabel(groupBox_6);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setMinimumSize(QSize(91, 20));

        gridLayout_3->addWidget(label_24, 1, 0, 1, 1);

        label_38 = new QLabel(groupBox_6);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setMinimumSize(QSize(91, 20));

        gridLayout_3->addWidget(label_38, 3, 0, 1, 1);

        doubleSpinBox_maxCentBrightness = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_maxCentBrightness->setObjectName(QStringLiteral("doubleSpinBox_maxCentBrightness"));
        doubleSpinBox_maxCentBrightness->setDecimals(1);

        gridLayout_3->addWidget(doubleSpinBox_maxCentBrightness, 3, 2, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 1, 3, 1, 1);

        doubleSpinBox_MinRadius = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_MinRadius->setObjectName(QStringLiteral("doubleSpinBox_MinRadius"));
        doubleSpinBox_MinRadius->setDecimals(0);

        gridLayout_3->addWidget(doubleSpinBox_MinRadius, 1, 2, 1, 1);

        label_22 = new QLabel(groupBox_6);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setMinimumSize(QSize(91, 20));

        gridLayout_3->addWidget(label_22, 0, 0, 1, 1);

        doubleSpinBox_MaxRadius = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_MaxRadius->setObjectName(QStringLiteral("doubleSpinBox_MaxRadius"));
        doubleSpinBox_MaxRadius->setDecimals(0);

        gridLayout_3->addWidget(doubleSpinBox_MaxRadius, 0, 2, 1, 1);

        label_19 = new QLabel(groupBox_6);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setMinimumSize(QSize(91, 20));

        gridLayout_3->addWidget(label_19, 2, 0, 1, 1);

        doubleSpinBox__MinDist = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox__MinDist->setObjectName(QStringLiteral("doubleSpinBox__MinDist"));
        doubleSpinBox__MinDist->setDecimals(0);

        gridLayout_3->addWidget(doubleSpinBox__MinDist, 2, 2, 1, 1);

        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_6, 0, 0, 2, 1);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_13 = new QGridLayout(tab_4);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        textBrowser = new QTextBrowser(tab_4);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_13->addWidget(textBrowser, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout_11->addWidget(tabWidget, 0, 0, 1, 3);

        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setMaximumSize(QSize(80, 16777215));

        gridLayout_11->addWidget(pushButton_exit, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\257\271\344\275\215\345\217\202\346\225\260\350\256\276\345\256\232", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "IPC\347\231\273\345\275\225\345\217\202\346\225\260", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "\345\257\206  \347\240\201\357\274\232", Q_NULLPTR));
        lineEdit_IP->setInputMask(QApplication::translate("MainWindow", "000.000.000.000", Q_NULLPTR));
        lineEdit_IP->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label_30->setText(QApplication::translate("MainWindow", "IP\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        groupBox_DispOSD->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\227\266\351\227\264\346\227\245\346\234\237", Q_NULLPTR));
        label_37->setText(QApplication::translate("MainWindow", "\345\235\220  \346\240\207 Y\357\274\232", Q_NULLPTR));
        comboBox_OSDHourType->clear();
        comboBox_OSDHourType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "24\345\260\217\346\227\266\345\210\266", Q_NULLPTR)
         << QApplication::translate("MainWindow", "12\345\260\217\346\227\266\345\210\266", Q_NULLPTR)
        );
        checkBox_DispWeek->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272", Q_NULLPTR));
        label_35->setText(QApplication::translate("MainWindow", "\345\235\220  \346\240\207 X\357\274\232", Q_NULLPTR));
        label_40->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\345\244\247\345\260\217\357\274\232", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "\345\260\217 \346\227\266 \345\210\266\357\274\232", Q_NULLPTR));
        comboBox_FontType->clear();
        comboBox_FontType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "16*16(\344\270\255)/8*16(\350\213\261)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "32*32(\344\270\255)/16*32(\350\213\261)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64*64(\344\270\255)/32*64(\350\213\261)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "48*48(\344\270\255)/24*48(\350\213\261)", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\350\207\252\351\200\202\345\272\224(adaptive)", Q_NULLPTR)
        );
        label_36->setText(QApplication::translate("MainWindow", "\346\227\245\346\234\237\346\240\274\345\274\217\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\230\237    \346\234\237\357\274\232", Q_NULLPTR));
        comboBox_OSDType->clear();
        comboBox_OSDType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "XXXX-XX-XX \345\271\264\346\234\210\346\227\245", Q_NULLPTR)
         << QApplication::translate("MainWindow", "XX-XX-XXXX \346\234\210\346\227\245\345\271\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "XXXX\345\271\264XX\346\234\210XX\346\227\245", Q_NULLPTR)
         << QApplication::translate("MainWindow", "XX\346\234\210XX\346\227\245XXXX\345\271\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "XX-XX-XXXX \346\227\245\346\234\210\345\271\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "XX\346\227\245XX\346\234\210XXXX\345\271\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "xx/xx/xxxx \346\234\210/\346\227\245/\345\271\264", Q_NULLPTR)
         << QApplication::translate("MainWindow", "xxxx/xx/xx \345\271\264/\346\234\210/\346\227\245", Q_NULLPTR)
         << QApplication::translate("MainWindow", "xx/xx/xxxx \346\227\245/\346\234\210/\345\271\264", Q_NULLPTR)
        );
        groupBox_ChannalName->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\351\200\232\351\201\223\345\220\215", Q_NULLPTR));
        label_41->setText(QApplication::translate("MainWindow", "\345\235\220\346\240\207Y\357\274\232", Q_NULLPTR));
        lineEdit_ChanNameX->setInputMask(QApplication::translate("MainWindow", "0000", Q_NULLPTR));
        label_42->setText(QApplication::translate("MainWindow", "\345\220\215 \347\247\260\357\274\232", Q_NULLPTR));
        label_34->setText(QApplication::translate("MainWindow", "\345\235\220\346\240\207X\357\274\232", Q_NULLPTR));
        lineEdit_ChanNameY->setInputMask(QApplication::translate("MainWindow", "0000", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_0), QApplication::translate("MainWindow", "\346\221\204\345\203\217\346\234\272\345\217\202\346\225\260", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "\351\242\204\350\247\210\345\233\276\345\203\217", Q_NULLPTR));
        checkBox_MixedImage->setText(QApplication::translate("MainWindow", "\350\260\203\350\257\225\344\277\241\346\201\257", Q_NULLPTR));
        checkBox_GrayImage->setText(QApplication::translate("MainWindow", "ROI", Q_NULLPTR));
        checkBox_FiltedImage->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\345\220\216\345\233\276\345\203\217", Q_NULLPTR));
        checkBox_EdgeImage->setText(QApplication::translate("MainWindow", "\350\275\256\345\273\223\345\233\276", Q_NULLPTR));
        checkBox_AccImage->setText(QApplication::translate("MainWindow", "hough\347\264\257\345\212\240\345\231\250", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206", Q_NULLPTR));
        label_45->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\345\274\272\345\272\246\357\274\232", Q_NULLPTR));
        comboBox_DownSampling->clear();
        comboBox_DownSampling->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\216\237\345\247\213\345\260\272\345\257\270", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1920*1080", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1280*720", Q_NULLPTR)
         << QApplication::translate("MainWindow", "960*540", Q_NULLPTR)
         << QApplication::translate("MainWindow", "640*360", Q_NULLPTR)
         << QApplication::translate("MainWindow", "480*270", Q_NULLPTR)
        );
        label_43->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\351\231\215\351\207\207\346\240\267\357\274\232", Q_NULLPTR));
        label_44->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        comboBox_FiltType->clear();
        comboBox_FiltType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\270\215\346\273\244\346\263\242", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\235\207\345\200\274\346\273\244\346\263\242", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\253\230\346\226\257\346\273\244\346\263\242", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\344\270\255\345\200\274\346\273\244\346\263\242", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\345\217\214\350\276\271\346\273\244\346\263\242", Q_NULLPTR)
        );
        label_23->setText(QApplication::translate("MainWindow", "canny\351\230\210\345\200\2741\357\274\232", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "canny\351\230\210\345\200\2742\357\274\232", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "hough\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "hough DP\357\274\232", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206\351\231\220\346\227\266", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "ms", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "\345\233\276\345\203\217\345\244\204\347\220\206\345\217\202\346\225\260", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "\347\233\256\346\240\207\350\256\276\345\256\232\344\275\215\347\275\256", Q_NULLPTR));
        label_56->setText(QApplication::translate("MainWindow", "%", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "x\357\274\232", Q_NULLPTR));
        label_55->setText(QApplication::translate("MainWindow", "%", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "y\357\274\232", Q_NULLPTR));
        groupBox_ReaultFilter->setTitle(QApplication::translate("MainWindow", "\345\235\220\346\240\207\346\273\244\346\263\242", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "\350\267\237\350\270\252\351\200\237\345\272\246\357\274\232", Q_NULLPTR));
        label_58->setText(QApplication::translate("MainWindow", "pix", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\346\273\244\346\263\242\345\215\212\345\276\204\357\274\232", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\243\200\346\265\213\345\214\272\345\237\237\351\231\220\345\256\232", Q_NULLPTR));
        label_48->setText(QApplication::translate("MainWindow", "\345\217\263\357\274\232", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "\345\267\246\357\274\232", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "\344\270\212\357\274\232", Q_NULLPTR));
        label_60->setText(QApplication::translate("MainWindow", "\344\270\213\357\274\232", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\347\233\256\346\240\207\346\243\200\346\265\213", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_39->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\347\233\270\345\257\271\344\272\216\345\233\276\345\203\217\345\256\275\345\272\246</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        label_39->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>\347\233\270\345\257\271\344\272\216\345\233\276\345\203\217\347\232\204\345\256\275\345\272\246</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        label_39->setText(QApplication::translate("MainWindow", "%", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_46->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\347\233\270\345\257\271\344\272\216\345\233\276\345\203\217\345\256\275\345\272\246</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_46->setText(QApplication::translate("MainWindow", "pix", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\215\212\345\276\204(\346\234\200\345\260\217)\357\274\232", Q_NULLPTR));
        label_38->setText(QApplication::translate("MainWindow", "\344\270\255\345\277\203\344\272\256\345\272\246(\346\234\200\351\253\230)\357\274\232", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_15->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\347\233\270\345\257\271\344\272\216\345\233\276\345\203\217\345\256\275\345\272\246</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_15->setText(QApplication::translate("MainWindow", "pix", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\345\215\212\345\276\204(\346\234\200\345\244\247)\357\274\232", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "\345\234\206\345\277\203\351\227\264\350\267\235(\346\234\200\345\260\217)\357\274\232", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>\347\233\270\345\257\271\344\272\216\345\233\276\345\203\217\345\256\275\345\272\246</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MainWindow", "pix", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\257\271\344\275\215\345\217\202\346\225\260", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                  <span style=\" font-weight:600;\">  \345\244\247\351\271\244\347\256\241\350\207\252\345\212\250\345\257\271\344\275\215\350\256\276\347\275\256\350\275\257\344\273\266</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; "
                        "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                  \350\277\236\344\272\221\346\270\257\350\277\234\346\264\213\346\265\201\344\275\223\350\243\205\345\215\270\350\256\276\345\244\207\346\234\211\351\231\220\345\205\254\345\217\270</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                       \347\237\263\345\214\226\345\267\245\347\250\213\344\272\213\344\270\232\351\203\250</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                             \350\265\265\347\221\236    18761309466</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                           "
                        "  zhaorui4142@163.com</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                                  </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">  </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">                                       \347\211\210\346\235\203\346\211\200\346\234\211</p></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        pushButton_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
