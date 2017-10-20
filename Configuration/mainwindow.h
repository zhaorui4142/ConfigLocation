#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "struct-data.h"
#include "glwidget/glwidget.h"
#include "videosource/videosource.h"
#include "detector/detector.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_checkBox_GrayImage_toggled(bool checked);
    void on_checkBox_MixedImage_toggled(bool checked);
    void on_ParamChanged(void);
    void on_posChanged(qreal top, qreal bottom, qreal left, qreal right, qreal exp_x, qreal exp_y);

    void on_groupBox_7_toggled(bool arg1);

    void on_checkBox_FiltedImage_toggled(bool checked);

    void on_checkBox_EdgeImage_toggled(bool checked);

    void on_checkBox_AccImage_toggled(bool checked);

private:
    void connectSignals(void);
    void setParamToUI(void);
    void getParamFromUI(void);
    void getParamFromFile(const QString &fileName);
    void setParamToFile(const QString &fileName);

    ParamtersForDetector detector_param;
    ParamtersForIPCamera video_source_param;
    Ui::MainWindow *ui;
    GlWidget *widgetColor,*widgetGray, *widgetBlur,*widgetEdge,*widgetHough;
    VideoSource *video_source;
    Detector *detector;


    QTimer cpu_usage_timer;
    bool param_changed;
};

#endif // MAINWINDOW_H
