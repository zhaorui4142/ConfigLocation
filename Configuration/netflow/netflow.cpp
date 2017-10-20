#include "netflow.h"

//���캯��
NetFlow::NetFlow(QObject *parent) : QObject(parent)
{
    m_pTable = NULL;
    m_dwAdapters = 0;
    uRetCode = GetIfTable(m_pTable, (PULONG)&m_dwAdapters, TRUE);
    //if (uRetCode == ERROR_NOT_SUPPORTED) return;
    if (uRetCode == ERROR_INSUFFICIENT_BUFFER)
    {   //����˿���������65535��
        m_pTable = (PMIB_IFTABLE)new BYTE[65535];
    }
    QObject::connect(&timer, &QTimer::timeout, this, &NetFlow::calcFlow);
    timer.start(1000);
}

//��������
NetFlow::~NetFlow()
{
    delete [] m_pTable;
}

//��ȡ�����ٶ�
int NetFlow::getDownloadingSpeed()
{
    return dwBandIn;
}

//��ȡ�ϴ��ٶ�
int NetFlow::getUploadingSpeed()
{
    return dwBandOut;
}

//��������
void NetFlow::calcFlow()
{
    NetSpeedInfo.clear();
    GetIfTable(m_pTable, (PULONG)&m_dwAdapters, TRUE);
    DWORD   dwInOctets = 0;
    DWORD   dwOutOctets = 0;

    //�����ж˿ڵ���������ͳ��
    for (UINT i = 0; i < m_pTable->dwNumEntries; i++)
    {
        MIB_IFROW   Row = m_pTable->table[i];
        dwInOctets += Row.dwInOctets;
        dwOutOctets += Row.dwOutOctets;
    }

    dwBandIn = dwInOctets - dwLastIn;       //�����ٶ�
    dwBandOut = dwOutOctets - dwLastOut;    //�ϴ�����
    if (dwLastIn <= 0)
    {
        dwBandIn = 0;
    }
    else
    {
        dwBandIn = dwBandIn / 1024;     //bת����kb
    }

    if (dwLastOut <= 0)
    {
        dwBandOut = 0;
    }
    else
    {
        dwBandOut = dwBandOut / 1024;   //bת����kb
    }

    dwLastIn = dwInOctets;
    dwLastOut = dwOutOctets;

    NetSpeedInfo = QString::fromLocal8Bit("�յ��ֽ�: %1 bytes\r\n �����ֽڣ� %2 bytes\r\n �����ٶ�: %3 Kb/s\r\n �����ٶ�: %4 kb/s\r\n")
                            .arg(dwLastIn).arg(dwLastOut).arg(dwBandIn).arg(dwBandOut);

    emit netspeedResult(NetSpeedInfo);
}
