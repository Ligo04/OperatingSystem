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
    std::queue<PCB*> m_PCBQueue{};         //���̵ľ�������
    std::queue<PCB*> m_PCBFQueue{};        //��ɶ���
    PCB* currPCB;                          //��ǰ�������еĽ���
    int m_TimeSlice=0;                     //ʱ��Ƭ
    int m_CurrSilce=0;                     //��ǰʱ��Ƭ
};

