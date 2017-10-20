#include "netflow.h"

//构造函数
NetFlow::NetFlow(QObject *parent) : QObject(parent)
{
    m_pTable = NULL;
    m_dwAdapters = 0;
    uRetCode = GetIfTable(m_pTable, (PULONG)&m_dwAdapters, TRUE);
    //if (uRetCode == ERROR_NOT_SUPPORTED) return;
    if (uRetCode == ERROR_INSUFFICIENT_BUFFER)
    {   //假设端口数不超过65535个
        m_pTable = (PMIB_IFTABLE)new BYTE[65535];
    }
    QObject::connect(&timer, &QTimer::timeout, this, &NetFlow::calcFlow);
    timer.start(1000);
}

//析构函数
NetFlow::~NetFlow()
{
    delete [] m_pTable;
}

//读取下载速度
int NetFlow::getDownloadingSpeed()
{
    return dwBandIn;
}

//读取上传速度
int NetFlow::getUploadingSpeed()
{
    return dwBandOut;
}

//计算流量
void NetFlow::calcFlow()
{
    NetSpeedInfo.clear();
    GetIfTable(m_pTable, (PULONG)&m_dwAdapters, TRUE);
    DWORD   dwInOctets = 0;
    DWORD   dwOutOctets = 0;

    //将所有端口的流量进行统计
    for (UINT i = 0; i < m_pTable->dwNumEntries; i++)
    {
        MIB_IFROW   Row = m_pTable->table[i];
        dwInOctets += Row.dwInOctets;
        dwOutOctets += Row.dwOutOctets;
    }

    dwBandIn = dwInOctets - dwLastIn;       //下载速度
    dwBandOut = dwOutOctets - dwLastOut;    //上床速速
    if (dwLastIn <= 0)
    {
        dwBandIn = 0;
    }
    else
    {
        dwBandIn = dwBandIn / 1024;     //b转换成kb
    }

    if (dwLastOut <= 0)
    {
        dwBandOut = 0;
    }
    else
    {
        dwBandOut = dwBandOut / 1024;   //b转换成kb
    }

    dwLastIn = dwInOctets;
    dwLastOut = dwOutOctets;

    NetSpeedInfo = QString::fromLocal8Bit("收到字节: %1 bytes\r\n 发送字节： %2 bytes\r\n 下行速度: %3 Kb/s\r\n 上行速度: %4 kb/s\r\n")
                            .arg(dwLastIn).arg(dwLastOut).arg(dwBandIn).arg(dwBandOut);

    emit netspeedResult(NetSpeedInfo);
}
