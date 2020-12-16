#pragma once
#include "PCB.h"
#include <vector>

class ProcessScheduling
{
public:
	ProcessScheduling(): m_PCBs(std::vector<PCB>()),m_ScheCount(0),m_IsRun(false){};
	virtual ~ProcessScheduling() {};
	virtual void Scheuduled() = 0;


	void Show();
	bool IsEnd();
	void Enter(PCB pcb) { this->m_PCBs.push_back(pcb); };
protected:
	std::vector<PCB> m_PCBs;		//��ǰ��Ҫ���ȵĽ���
	int m_ScheCount;			//��ǰ�ĵ��ȴ���
	bool m_IsRun;               //�Ƿ��н�����������
};


