#pragma once
#include <queue>
#include "PCB.h"
class RR 
{
public:
    RR(int timeslice=1);
     ~RR();
    void Scheuduled();
    void RandomBlockPCB();
    void Enter(PCB* pcb);
    PCB* GetRentPCB();
public:
    std::queue<PCB*> m_PCBQueue{};         //进程的就绪队列
    std::queue<PCB*> m_PCBFQueue{};        //完成队列
    std::queue<PCB*> m_PCBBlockQueue{};        //阻塞队列
    PCB* currPCB;                          //当前正在运行的进程
    int m_TimeSlice=0;                     //时间片
    int m_CurrSilce=0;                     //当前时间片
    bool             m_IsRun;              //是否开始
};

