#include "RR.h"
#include <iostream>

RR::RR(int timeslice)
	:m_TimeSlice(timeslice), m_CurrSilce(0), currPCB(nullptr),m_IsRun(false)
{
	
}

RR::~RR()
{
	for (size_t i = 0; i < m_PCBQueue.size(); ++i)
	{
		m_PCBQueue.pop();
	}
	for (size_t i = 0; i < m_PCBFQueue.size(); ++i)
	{
		m_PCBFQueue.pop();
	}
	if (currPCB != nullptr)
	{
		delete currPCB;
		currPCB = nullptr;
	}
}

void RR::Scheuduled()
{
	if (!m_IsRun)
	{
		currPCB = GetRentPCB();
		if (currPCB != nullptr)
		{
			this->m_PCBQueue.pop();
			currPCB->currStatus = PCB::Status::Run;
			m_IsRun = true;
			currPCB->ranTime++;
			m_CurrSilce++;
		}
		return;
	}
	if (m_CurrSilce == m_TimeSlice|| currPCB->ranTime == currPCB->needTime)
	{
		//调度
		if (currPCB->ranTime == currPCB->needTime)
		{
			currPCB->currStatus = PCB::Status::Finish;
			this->m_PCBFQueue.push(currPCB);
		}
		else
		{
			currPCB->currStatus = PCB::Status::Wait;
			this->m_PCBQueue.push(currPCB);
		}

		currPCB = GetRentPCB();
		if (currPCB != nullptr)
		{
			this->m_PCBQueue.pop();
			currPCB->currStatus = PCB::Status::Run;
			currPCB->ranTime++;
		}
		else
		{
			m_CurrSilce = 0;
			currPCB = nullptr;
			m_IsRun = false;
		}
	}
	else
	{
		currPCB->ranTime++;
	}

	m_CurrSilce = (m_CurrSilce + 1) % (m_TimeSlice + 1);
	if (m_CurrSilce == 0)
	{
		m_CurrSilce += 1;
	}
}

void RR::RandomBlockPCB()
{
	int select = random_int(0, m_PCBQueue.size());
	if (select == 0)
	{
		if (currPCB != nullptr)
		{
			//阻塞正在运行的进程
			m_PCBBlockQueue.push(currPCB);
			m_CurrSilce = 0;
			currPCB = nullptr;
			m_IsRun = false;
		}
	}
	else
	{
		//阻塞其他进程
		for (size_t i = 0; i < m_PCBQueue.size(); ++i)
		{
			PCB* pcb = m_PCBQueue.front();
			m_PCBQueue.pop();
			if (i == static_cast<unsigned long long>(select) - 1)
			{
				//阻塞进程
				m_PCBBlockQueue.push(pcb);
			}
			else
			{
				m_PCBBlockQueue.push(pcb);
			}
		}
	}
}

void RR::Enter(PCB* pcb)
{
	this->m_PCBQueue.push(pcb);
}

PCB* RR::GetRentPCB()
{
	if(m_PCBQueue.empty())
		return nullptr;

	return m_PCBQueue.front();
}
