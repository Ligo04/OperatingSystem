#include "ProcessScheduling.h"
#include<iostream>


void ProcessScheduling::Show()
{
	std::string str = "-------------------------��" + std::to_string(m_ScheCount++) + "�ε���-------------------------\n";
	std::string runstr = "---------�������еĽ���---------\n";
	std::string waitstr = "---------�������еĽ���---------\n";
	std::string finishstr = "---------��ɵĽ���---------\n";
	for (auto& p : m_PCBs)
	{
		if (p.currStatus == PCB::Status::Run)
		{
			runstr += "����" + p.name + ":{\n";
			runstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
			runstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
			runstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
			runstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
		}
		else if (p.currStatus == PCB::Status::Wait)
		{
			waitstr += "����" + p.name + ":{\n";
			waitstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
			waitstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
			waitstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
			waitstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
		}
		else if (p.currStatus == PCB::Status::Finish)
		{
			finishstr += "����" + p.name + ":{\n";
			finishstr += "    ���̵ĵ���ʱ�䣺" + std::to_string(p.arriveTime) + "\n";
			finishstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p.waitTime) + "\n";
			finishstr += "    ������Ҫ������ʱ�䣺" + std::to_string(p.needTime) + "\n";
			finishstr += "    ����������ʱ�䣺" + std::to_string(p.ranTime) + "\n}\n";
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
