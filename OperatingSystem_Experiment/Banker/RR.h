#pragma once
#include "ProcessScheduling.h"
#include <queue>
class RR :
    public ProcessScheduling
{
public:
    RR(int timeslice=1);
    virtual ~RR();
    virtual void Scheuduled();
    void Enter(PCB* pcb);
    void Show();
    bool IsEnd();
    PCB* GetRentPCB();
protected:
    std::queue<PCB*> m_PCBQueue{};         //进程的就绪队列
    std::queue<PCB*> m_PCBFQueue{};        //完成队列
    PCB* currPCB;                          //当前正在运行的进程
    int m_TimeSlice=0;                     //时间片
    int m_CurrSilce=0;                     //当前时间片
};

