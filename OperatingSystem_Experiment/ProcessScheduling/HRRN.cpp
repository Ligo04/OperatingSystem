#include "HRRN.h"

HRRN::HRRN()
{
}

HRRN::~HRRN()
{
	this->m_PCBs.clear();
}

void HRRN::Scheuduled()
{
	if (!m_IsRun && !m_PCBs.empty())
	{
		PCB* pcb0 = GetMaxRRPCB();
		if (pcb0 != nullptr)
		{
			pcb0->currStatus = PCB::Status::Run;
			Show();
			m_PCBs.front().ranTime++;
			m_IsRun = true;
		}
		return;
	}

	PCB* flagPCB = nullptr;
	for (auto& p : m_PCBs)
	{
		if (p.currStatus == PCB::Status::Run)
		{
			if (p.ranTime == p.needTime)
			{
				//��������
				p.currStatus = PCB::Status::Finish;
				//�ҵ���һ����Ҫ���ȵĽ���

				flagPCB = GetMaxRRPCB();
				if (flagPCB != nullptr)
				{
					flagPCB->currStatus = PCB::Status::Run;
					//������
					Show();
					flagPCB->ranTime++;
				}
				else
				{
					Show();
					m_IsRun = false;
				}
			}
			else
			{
				if (&p != flagPCB)
				{
					p.ranTime++;
				}
			}
		}
		else if (p.currStatus == PCB::Status::Wait)
		{
			p.waitTime++;
		}
	}
}

PCB* HRRN::GetMaxRRPCB()
{
	if (m_PCBs.empty())
	{
		return nullptr;
	}
	float maxRR = 0.0f;
	PCB* pcb = nullptr;
	for (auto& p : m_PCBs)
	{
		if (p.currStatus == PCB::Status::Wait)
		{
			float RR = (float)(p.waitTime + p.needTime) / (p.needTime);
			if (RR > maxRR)
			{
				maxRR = RR;
				pcb = &p;
			}
		}
	}
	return pcb;
}
