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
    std::vector<int> m_TotalNum;           //�ܵ���Դ����
    std::queue<PCB*> m_PCBQueue{};         //���̵ľ�������
    std::queue<PCB*> m_PCBFQueue{};        //��ɶ���
    std::queue<PCB*> m_PCBBQueue{};        //��������
    PCB* currPCB;                          //��ǰ�������еĽ���
    int m_TimeSlice=0;                     //ʱ��Ƭ
    int m_CurrSilce=1;                     //��ǰʱ��Ƭ
    int m_ScheCount = 0;                   //���ȴ���
};

