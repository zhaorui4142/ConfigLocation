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
    DWORD   dwLastIn = 0;           //��һ���ӵĽ����ֽ���
    DWORD   dwLastOut = 0;          //��һ���ӵķ����ֽ���
    DWORD   dwBandIn = 0;           //�����ٶ�
    DWORD   dwBandOut = 0;          //�ϴ��ٶ�
    QTimer timer;

};

#endif // NETFLOW_H
