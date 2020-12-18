#pragma once
#include <queue>
#include "PCB.h"


class Banker
{
public:
    Banker(std::vector<int> total,int timeslice=1);
     ~Banker();
    void Scheuduled();
    void Enter(PCB* pcb);
    void Show();
    bool IsEnd();
    PCB* GetRentPCB();
    std::vector<int> GetResources();
    void ReturnResoureces(std::vector<int> res);
    bool CheckIsSafe(std::vector<int> changeNums);
protected:
    std::vector<int> m_TotalNum;           //总的资源总数
    std::queue<PCB*> m_PCBQueue{};         //进程的就绪队列
    std::queue<PCB*> m_PCBFQueue{};        //完成队列
    std::queue<PCB*> m_PCBBQueue{};        //阻塞队列
    PCB* currPCB;                          //当前正在运行的进程
    int m_TimeSlice=0;                     //时间片
    int m_CurrSilce=1;                     //当前时间片
    int m_ScheCount = 0;                   //调度次数
};

