#include "cpuusage.h"
#include <QDebug>

//构造函数
CpuUsage::CpuUsage(QObject *parent) : QObject(parent)
{
    m_nUses.clear();
    m_nNumberProcessors=GetNumberProcessors();
    if (m_nNumberProcessors != -1)
    {
        m_nUses.resize(m_nNumberProcessors);
        m_nUses.fill(0);
        memset(m_nOidleTime,0,sizeof(m_nOidleTime));
        memset(m_nOkerenelTime,0,sizeof(m_nOidleTime));
        memset(m_nOuserTime,0,sizeof(m_nOidleTime));
        memset(m_nOdpctTime,0,sizeof(m_nOidleTime));

        m_ProcessInfo = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[m_nNumberProcessors];

        QObject::connect(&timer, &QTimer::timeout, this, &CpuUsage::CalProcessorsUses);
        timer.start(1000);
    }
}

//析构函数
CpuUsage::~CpuUsage()
{
    timer.stop();
    timer.deleteLater();
    QObject::disconnect(&timer, &QTimer::timeout, this, &CpuUsage::CalProcessorsUses);
    delete m_ProcessInfo;
}

//公有函数，获取CPU核心数
int CpuUsage::GetNumberProcessors()
{
    SYSTEM_BASIC_INFORMATION    m_SystemBaseInfo;
    PROCNTQSI   NtQuerySystemInformation;

    std::string lpcstr= "NtQuerySystemInformation";
    std::wstring modulehandle=QString("ntdll").toStdWString();
    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(modulehandle.c_str()),lpcstr.c_str());

    //NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle("ntdll"),"NtQuerySystemInformation");
    int status = NtQuerySystemInformation(SystemBasicInformation,&m_SystemBaseInfo,sizeof(m_SystemBaseInfo),NULL);
    if(status != NO_ERROR) return -1;
    return m_SystemBaseInfo.bKeNumberProcessors;
}

//公有函数，获取CPU使用率
int CpuUsage::GetUseage(const int nNumber)
{
    return m_nUses[nNumber];
}

//私有函数，计算CPU使用率，定时调用，1s一次
void CpuUsage::CalProcessorsUses()
{
    if(m_nNumberProcessors == -1) return;

    PROCNTQSI   NtQuerySystemInformation;
    __int64 nIdleTime=0,nKernelTime=0,nUserTime=0,nDpcTime=0,nInterruptTime=0,nTotalTime=0;

    std::string lpcstr= "NtQuerySystemInformation";
    std::wstring modulehandle=QString("ntdll").toStdWString();
    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(modulehandle.c_str()),lpcstr.c_str());//利用ntdll内置的API获取CPU

    int status=NtQuerySystemInformation(SystemProcessorPerformanceInformation, m_ProcessInfo, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * m_nNumberProcessors, 0);
    status;
    for (int i = 0; i < m_nNumberProcessors; i++)
    {
        nIdleTime = m_ProcessInfo[i].i64IdleTime - m_nOidleTime[i];
        nKernelTime = m_ProcessInfo[i].i64KernelTime - m_nOkerenelTime[i];
        nUserTime = m_ProcessInfo[i].i64UserTime - m_nOuserTime[i];
        nDpcTime = m_ProcessInfo[i].i64DpcTime -m_nOdpctTime[i];
        nInterruptTime = m_ProcessInfo[i].i64InterruptTime - m_nOinterruptTime[i];

        nTotalTime = nKernelTime + nUserTime + nDpcTime + nInterruptTime;
        m_nUses[i] =100*(nTotalTime-nIdleTime)/nTotalTime;    //计算CPU使用率

        m_nOidleTime[i] = m_ProcessInfo[i].i64IdleTime;
        m_nOkerenelTime[i] = m_ProcessInfo[i].i64KernelTime;
        m_nOuserTime[i] = m_ProcessInfo[i].i64UserTime;
        m_nOdpctTime[i] = m_ProcessInfo[i].i64DpcTime;
        m_nOinterruptTime[i] = m_ProcessInfo[i].i64InterruptTime;
    }
}
