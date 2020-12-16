#include "SJF.h"
#include<algorithm>
#include<iostream>

SJF::SJF()
{
}

SJF::~SJF()
{
	this->m_PCBs.clear();
}

void SJF::Scheuduled()
{
	if (!m_IsRun && !m_PCBs.empty())
	{
		PCB* pcb0 = GetMinNeedTime();
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

				flagPCB = GetMinNeedTime();
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

//void SJF::Show()
//{
//	static int i = 1;
//	std::string str = "-------------------------��"+std::to_string(i++)+"�ε���-------------------------\n";
//	std::string runstr = "---------�������еĽ���---------\n";
//	std::string waitstr = "---------�������еĽ���---------\n";
//	std::string finishstr = "---------��ɵĽ���---------\n";
//	for (auto& p : m_PCBs)
//	{
//		if (p.currStatus == PCB::Status::Run)
//		{
//			runstr += "����" + p.name + ":{\n";
//			runstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
//			runstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
//			runstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
//			runstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
//		}
//		else if (p.currStatus == PCB::Status::Wait)
//		{
//			waitstr += "����" + p.name + ":{\n";
//			waitstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
//			waitstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
//			waitstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
//			waitstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
//		}
//		else if (p.currStatus == PCB::Status::Finish)
//		{
//			finishstr += "����" + p.name + ":{\n";
//			finishstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
//			finishstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
//			finishstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
//			finishstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
//		}
//	}
//	runstr += "\n";
//	waitstr += "\n";
//	finishstr += "\n";
//	std::cout << str << runstr << waitstr << finishstr << std::endl;
//}

bool SJF::IsEnd()
{
	for (auto& p : m_PCBs)
	{
		if (p.currStatus == PCB::Status::Run || p.currStatus == PCB::Status::Wait)
		{
			return false;
		}
	}
	return true;
}

PCB* SJF::GetMinNeedTime()
{
	if (m_PCBs.empty())
	{
		return nullptr;
	}
	int minTime = 999;
	PCB* pcb = nullptr;
	for (auto& p : m_PCBs)
	{
		if ((p.needTime < minTime) && p.currStatus == PCB::Status::Wait)
		{
			minTime = p.needTime;
			pcb = &p;
		}
	}
	return pcb;
}
