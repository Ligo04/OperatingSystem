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
				//发生调度
				p.currStatus = PCB::Status::Finish;
				//找到下一个需要调度的进程

				flagPCB = GetMinNeedTime();
				if (flagPCB != nullptr)
				{
					flagPCB->currStatus = PCB::Status::Run;
					//输出结果
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
//	std::string str = "-------------------------第"+std::to_string(i++)+"次调度-------------------------\n";
//	std::string runstr = "---------正在运行的进程---------\n";
//	std::string waitstr = "---------就绪队列的进程---------\n";
//	std::string finishstr = "---------完成的进程---------\n";
//	for (auto& p : m_PCBs)
//	{
//		if (p.currStatus == PCB::Status::Run)
//		{
//			runstr += "进程" + p.name + ":{\n";
//			runstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
//			runstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
//			runstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
//			runstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
//		}
//		else if (p.currStatus == PCB::Status::Wait)
//		{
//			waitstr += "进程" + p.name + ":{\n";
//			waitstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
//			waitstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
//			waitstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
//			waitstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
//		}
//		else if (p.currStatus == PCB::Status::Finish)
//		{
//			finishstr += "进程" + p.name + ":{\n";
//			finishstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
//			finishstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
//			finishstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
//			finishstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
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
