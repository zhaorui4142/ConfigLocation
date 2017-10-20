#ifndef NETFLOW_H
#define NETFLOW_H

#include <QObject>
#include <QTimer>
//#include <winsock2.h>
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <winsock.h>
#include <iphlpapi.h>


class NetFlow : public QObject
{
    Q_OBJECT
public:
    explicit NetFlow(QObject *parent = 0);
    ~NetFlow();
    int getDownloadingSpeed(void);
    int getUploadingSpeed(void);

signals:
    void netspeedResult(QString);

public slots:

private:
    void calcFlow(void);
    QString         NetSpeedInfo;

    PMIB_IFTABLE    m_pTable;
    DWORD           m_dwAdapters = 0;
    ULONG           uRetCode;
    DWORD   dwLastIn = 0;           //上一秒钟的接收字节数
    DWORD   dwLastOut = 0;          //上一秒钟的发送字节数
    DWORD   dwBandIn = 0;           //下载速度
    DWORD   dwBandOut = 0;          //上传速度
    QTimer timer;

};

#endif // NETFLOW_H
