#ifndef CPUUSAGE_H
#define CPUUSAGE_H

//ͷ�ļ�������
#include <windows.h>
#include <QObject>
#include <QTimer>
#include <QVector>


#define SystemBasicInformation  0
#define SystemPerformanceInformation    2
#define SystemTimeInformation   3
#define SystemProcessorPerformanceInformation   8

typedef   LONG   (WINAPI   *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

//����ṹ��
typedef struct SYSTEM_BASIC
{
    DWORD   dwUnknown1;
    ULONG   uKeMaximumIncrement;
    ULONG   uPageSize;
    ULONG   uMmNumberOfPhysicalPages;
    ULONG   uMmLowestPhysicalPage;
    ULONG   uMmHighestPhysicalPage;
    ULONG   uAllocationGranularity;
    PVOID   pLowestUserAddress;
    PVOID   pMmHighestUserAddress;
    ULONG   uKeActiveProcessors;
    BYTE    bKeNumberProcessors;
    BYTE    bUnknown2;
    WORD    wUnknown3;
}SYSTEM_BASIC_INFORMATION;

//����ṹ��
typedef struct SYSTEM_PROCESSOR_PERFORMANCE
{
    __int64 i64IdleTime;
    __int64 i64KernelTime;
    __int64 i64UserTime;
    __int64 i64DpcTime;
    __int64 i64InterruptTime;
    long lInterruptCount;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;


//��������
class CpuUsage : public QObject
{
    Q_OBJECT
public:
    explicit CpuUsage(QObject *parent = 0);
    ~CpuUsage();
    int GetNumberProcessors();      //���CPU��������
    int GetUseage(const int nNumber);       //���CPUʹ���ʵ�ֵ


signals:

public slots:

private:
    void CalProcessorsUses();       //����CPUʹ����
    SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION *m_ProcessInfo;
    QVector<int> m_nUses;
    int m_nNumberProcessors;

    __int64 m_nOidleTime[5];    //�ɵ�CPUʱ�䣬���ڼ���CPUʹ����
    __int64 m_nOkerenelTime[5];
    __int64 m_nOuserTime[5];
    __int64 m_nOdpctTime[5];
    __int64 m_nOinterruptTime[5];

    QTimer timer;
};

#endif // CPUUSAGE_H
