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
    std::queue<PCB*> m_PCBQueue{};         //���̵ľ�������
    std::queue<PCB*> m_PCBFQueue{};        //��ɶ���
    std::queue<PCB*> m_PCBBlockQueue{};        //��������
    PCB* currPCB;                          //��ǰ�������еĽ���
    int m_TimeSlice=0;                     //ʱ��Ƭ
    int m_CurrSilce=0;                     //��ǰʱ��Ƭ
    bool             m_IsRun;              //�Ƿ�ʼ
};

