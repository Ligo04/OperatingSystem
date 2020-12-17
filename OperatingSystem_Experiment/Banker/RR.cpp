#include "RR.h"
#include <iostream>

RR::RR(int timeslice)
	:m_TimeSlice(timeslice), m_CurrSilce(0), currPCB(nullptr)
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
	delete currPCB;
	currPCB = nullptr;
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
			Show();
			currPCB->ranTime++;
			m_CurrSilce++;
		}
		return;
	}

	if (m_CurrSilce == m_TimeSlice)
	{
		//����
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
			Show();
			currPCB->ranTime++;
		}
		else
		{
			Show();
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

void RR::Enter(PCB* pcb)
{
	this->m_PCBQueue.push(pcb);
}

void RR::Show()
{
	
	std::string str = "-------------------------��" + std::to_string(m_ScheCount++) + "�ε���-------------------------\n";
	std::string runstr = "---------�������еĽ���---------\n";
	std::string waitstr = "---------�������еĽ���---------\n";
	std::string finishstr = "---------��ɵĽ���---------\n";

	if (currPCB != nullptr)
	{
		runstr += "����" + currPCB->name + ":{\n";
		runstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(currPCB->arriveTime) + "\n";
		runstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(currPCB->waitTime) + "\n";
		runstr += "    ������Ҫ������ʱ�䣺" + std::to_string(currPCB->needTime) + "\n";
		runstr += "    ����������ʱ�䣺" + std::to_string(currPCB->ranTime) + "\n}\n";
	}

	for(size_t i=0;i<m_PCBQueue.size();++i)
	{
		PCB* p = m_PCBQueue.front();

		waitstr += "����" + p->name + ":{\n";
		waitstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p->arriveTime) + "\n";
		waitstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p->waitTime) + "\n";
		waitstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p->needTime) + "\n";
		waitstr += "    ����������ʱ�䣺" + std::to_string(p->ranTime) + "\n}\n";
		m_PCBQueue.pop();
		m_PCBQueue.push(p);
	}

	for (size_t i = 0; i < m_PCBFQueue.size(); ++i)
	{
		PCB* p = m_PCBFQueue.front();

		finishstr += "����" + p->name + ":{\n";
		finishstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p->arriveTime) + "\n";
		finishstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p->waitTime) + "\n";
		finishstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p->needTime) + "\n";
		finishstr += "    ����������ʱ�䣺" + std::to_string(p->ranTime) + "\n}\n";
		m_PCBFQueue.pop();
		m_PCBFQueue.push(p);
	}
	runstr += "\n";
	waitstr += "\n";
	finishstr += "\n";
	std::cout << str << runstr << waitstr << finishstr << std::endl;
}

bool RR::IsEnd()
{
	if (m_PCBQueue.empty() && currPCB == nullptr)
		return true;
	return false;
}

PCB* RR::GetRentPCB()
{
	if(m_PCBQueue.empty())
		return nullptr;

	return m_PCBQueue.front();
}
