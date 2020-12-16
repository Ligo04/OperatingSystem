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
	std::vector<PCB> m_PCBs;		//当前需要调度的进程
	int m_ScheCount;			//当前的调度次数
	bool m_IsRun;               //是否有进程正在运行
};


