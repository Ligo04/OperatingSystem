#include "RR.h"

RR::RR()
	:currIndex(0)
{
	
}

RR::~RR()
{
}

void RR::Scheuduled()
{
	if (!m_IsRun && !m_PCBs.empty())
	{
		PCB* pcb = GetRentPCB();
		if (pcb->currStatus == PCB::Status::Wait)
		{
			pcb->currStatus = PCB::Status::Run;
			pcb->ranTime++;
			return;
		}
	}
	
	PCB* flagPCB = GetRentPCB();
	if (flagPCB != nullptr)
	{
		
	}
	else
	{
		Show();
		m_IsRun = false;
	}
}

PCB* RR::GetRentPCB()
{
	if(m_PCBs.empty())
		return nullptr;
	size_t index = currIndex;
	while (true)
	{
		index = (index + 1) % m_PCBs.size();
		if (m_PCBs[index].currStatus == PCB::Status::Wait)
		{
			currIndex = index;
			return &m_PCBs[index];
		}
		if (index == currIndex)
		{
			if (m_PCBs[index].currStatus == PCB::Status::Run)
			{
				return &m_PCBs[index];
			}
			else
			{
				return nullptr;
			}
		}
		
		index++;
	}
}
