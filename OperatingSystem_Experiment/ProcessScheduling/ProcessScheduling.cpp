#include "ProcessScheduling.h"
#include<iostream>


void ProcessScheduling::Show()
{
	std::string str = "-------------------------第" + std::to_string(m_ScheCount++) + "次调度-------------------------\n";
	std::string runstr = "---------正在运行的进程---------\n";
	std::string waitstr = "---------就绪队列的进程---------\n";
	std::string finishstr = "---------完成的进程---------\n";
	for (auto& p : m_PCBs)
	{
		if (p.currStatus == PCB::Status::Run)
		{
			runstr += "进程" + p.name + ":{\n";
			runstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
			runstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
			runstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
			runstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
		}
		else if (p.currStatus == PCB::Status::Wait)
		{
			waitstr += "进程" + p.name + ":{\n";
			waitstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
			waitstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
			waitstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
			waitstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
		}
		else if (p.currStatus == PCB::Status::Finish)
		{
			finishstr += "进程" + p.name + ":{\n";
			finishstr += "    进程的到达时间：" + std::to_string(p.arriveTime) + "\n";
			finishstr += "    进程的等待时间：" + std::to_string(p.waitTime) + "\n";
			finishstr += "    进程需要的运行时间：" + std::to_string(p.needTime) + "\n";
			finishstr += "    进程已运行时间：" + std::to_string(p.ranTime) + "\n}\n";
		}
	}
	runstr += "\n";
	waitstr += "\n";
	finishstr += "\n";
	std::cout << str << runstr << waitstr << finishstr << std::endl;

	
}

bool ProcessScheduling::IsEnd()
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
