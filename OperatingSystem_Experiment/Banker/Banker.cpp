#include "Banker.h"
#include <iostream>

Banker::Banker(std::vector<int> total,int timeslice)
	:m_TotalNum(total),m_TimeSlice(timeslice), m_CurrSilce(1), currPCB(nullptr)
{
	
}

Banker::~Banker()
{
	m_TotalNum.clear();
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

void Banker::Scheuduled()
{
	if (m_CurrSilce == m_TimeSlice)
	{
		if (currPCB != nullptr)
		{
			//调度进程
			currPCB->currStatus = PCB::Status::Wait;
			this->m_PCBQueue.push(currPCB);
			currPCB = nullptr;
		}
		while (true)
		{
			currPCB = GetRentPCB();
			if (currPCB != nullptr)
			{
				this->m_PCBQueue.pop();
				currPCB->currStatus = PCB::Status::Run;
				std::vector<int> res = GetResources();				//申请资源
				while (!currPCB->IsCanDis(res))						//判断是否申请合理
				{
					res = GetResources();
					continue;
				}

				if (CheckIsSafe(res))
				{
					currPCB->AddResource(res);
					for (size_t i = 0; i < res.size(); i++)
					{
						m_TotalNum[i] -= res[i];
					}
					//安全
					if (currPCB->IsMaxResource())
					{
						//达到最大需求
						currPCB->ranTime++;
						currPCB->currStatus = PCB::Status::Finish;
						this->m_PCBFQueue.push(currPCB);
						ReturnResoureces(currPCB->disNums);
						currPCB = nullptr;
						m_CurrSilce = 0;
					}
					else
					{
						//没达到最大需求
						currPCB->ranTime++;
					}
					Show();
					break;
				}
				else
				{
					//不安全
					currPCB->currStatus = PCB::Status::Block;			//阻塞
					this->m_PCBBQueue.push(currPCB);
					Show();
					continue;
				}
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		if (currPCB != nullptr)
		{
			currPCB->ranTime++;
		}
	}

	m_CurrSilce = (m_CurrSilce + 1) % (m_TimeSlice + 1);
	if (m_CurrSilce == 0)
	{
		m_CurrSilce += 1;
	}
}

void Banker::Enter(PCB* pcb)
{
	this->m_PCBQueue.push(pcb);
}

void Banker::Show()
{
	
	std::string str = "-------------------------第" + std::to_string(m_ScheCount++) + "次调度-------------------------\n";
	std::string runstr = "---------正在运行的进程---------\n";
	std::string waitstr = "---------就绪队列的进程---------\n";
	std::string blockstr = "---------阻塞队列的进程---------\n";
	std::string finishstr = "---------完成的进程---------\n";

	if (currPCB != nullptr)
	{
		runstr += "进程" + currPCB->name + ":{\n";
		runstr += "    进程的等待时间：" + std::to_string(currPCB->waitTime) + "\n";
		runstr += "    进程已运行时间：" + std::to_string(currPCB->ranTime) + "\n";
		runstr += "    进程的所需要的资源数：";
		for (auto& num : currPCB->needNums)
		{
			runstr += std::to_string(num) + "  ";
		}
		runstr += "\n";
		runstr += "    进程的已分配的资源数：";
		for (auto& num : currPCB->disNums)
		{
			runstr += std::to_string(num) + "  ";
		}
		runstr += "\n}\n\n";
	}

	for(size_t i=0;i<m_PCBQueue.size();++i)
	{
		PCB* p = m_PCBQueue.front();

		waitstr += "进程" + p->name + ":{\n";
		waitstr += "    进程的等待时间：" + std::to_string(p->waitTime) + "\n";
		waitstr += "    进程已运行时间：" + std::to_string(p->ranTime) + "\n";
		waitstr += "    进程的所需要的资源数：";
		for (auto& num : p->needNums)
		{
			waitstr += std::to_string(num) + "  ";
		}
		waitstr += "\n";
		waitstr += "    进程的已分配的资源数：";
		for (auto& num : p->disNums)
		{
			waitstr += std::to_string(num) + "  ";
		}
		waitstr += "\n}\n\n";


		m_PCBQueue.pop();
		m_PCBQueue.push(p);
	}

	for (size_t i = 0; i < m_PCBBQueue.size(); ++i)
	{
		PCB* p = m_PCBBQueue.front();

		blockstr += "进程" + p->name + ":{\n";
		blockstr += "    进程的等待时间：" + std::to_string(p->waitTime) + "\n";
		blockstr += "    进程已运行时间：" + std::to_string(p->ranTime) + "\n";
		blockstr += "    进程的所需要的资源数：";
		for (auto& num : p->needNums)
		{
			blockstr += std::to_string(num) + "  ";
		}
		blockstr += "\n";
		blockstr += "    进程的已分配的资源数：";
		for (auto& num : p->disNums)
		{
			blockstr += std::to_string(num) + "  ";
		}
		blockstr += "\n}\n\n";

		m_PCBBQueue.pop();
		m_PCBBQueue.push(p);
	}

	for (size_t i = 0; i < m_PCBFQueue.size(); ++i)
	{
		PCB* p = m_PCBFQueue.front();

		finishstr += "进程" + p->name + ":{\n";
		finishstr += "    进程的等待时间：" + std::to_string(p->waitTime) + "\n";
		finishstr += "    进程已运行时间：" + std::to_string(p->ranTime) + "\n";
		finishstr += "    进程的所需要的资源数：";
		for (auto& num : p->needNums)
		{
			finishstr += std::to_string(num) + "  ";
		}
		finishstr += "\n";
		finishstr += "    进程的已分配的资源数：";
		for (auto& num : p->disNums)
		{
			finishstr += std::to_string(num) + "  ";
		}
		finishstr += "\n}\n\n";


		m_PCBFQueue.pop();
		m_PCBFQueue.push(p);
	}

	runstr += "\n";
	waitstr += "\n";
	blockstr += "\n";
	finishstr += "\n";
	std::cout << str << runstr << waitstr << blockstr << finishstr << std::endl;
}

bool Banker::IsEnd()
{
	if (m_PCBQueue.empty() && currPCB == nullptr&& m_PCBBQueue.empty())
		return true;
	return false;
}

PCB* Banker::GetRentPCB()
{
	if (m_PCBQueue.empty())
	{
		if (m_PCBBQueue.empty())
		{
			return nullptr;
		}
		else
		{
			PCB* pcb = m_PCBBQueue.front();
			m_PCBBQueue.pop();
			pcb->currStatus = PCB::Status::Wait;
			m_PCBQueue.push(pcb);
			return pcb;
		}
	}

	return m_PCBQueue.front();
}

std::vector<int> Banker::GetResources()
{
	std::vector<int> resources;
	for (size_t i = 0; i < m_TotalNum.size(); ++i)
	{
		int num = 0;//random_int(0, currPCB->needNums[i] - currPCB->disNums[i]);
		if (m_TotalNum[i] != 0)
		{
			num = random_int(0, currPCB->needNums[i] - currPCB->disNums[i]);
		}
		resources.push_back(num);
	}
	return resources;
}

void Banker::ReturnResoureces(std::vector<int> res)
{
	if (currPCB == nullptr)
		return;
	for (size_t i = 0; i < res.size(); ++i)
	{
		m_TotalNum[i] += res[i];
	}
}

bool Banker::CheckIsSafe(std::vector<int> changeNums)
{
	//先判断是否可以满足剩下资源能不能这次分配
	for (size_t i = 0; i < changeNums.size(); ++i)
	{
		if (m_TotalNum[i] - changeNums[i] < 0)
		{
			return false;
		}
	}

	std::vector<int> remain = m_TotalNum;
	for (size_t i = 0; i < changeNums.size(); ++i)
	{
		changeNums[i] += currPCB->needNums[i];						//回收资源
	}

	for (size_t i = 0; i < m_PCBQueue.size(); ++i)
	{
		for (size_t j = 0; j < remain.size(); ++j)
		{
			remain[j] = remain[j] + changeNums[j];					//更新剩余可用资源
		}
		PCB* temppcb = m_PCBQueue.front();
		for (size_t j = 0; j < remain.size(); ++j)
		{
			if (remain[j] - (temppcb->needNums[j] - temppcb->disNums[j]) < 0)
			{
				return false;
			}
			changeNums[j] = temppcb->needNums[j];					//回收资源		
		}
		m_PCBQueue.pop();
		m_PCBQueue.push(temppcb);
	}

	for (size_t i = 0; i < m_PCBBQueue.size(); ++i)
	{
		for (size_t j = 0; j < remain.size(); ++j)
		{
			remain[j] = remain[j] + changeNums[j];					//更新剩余可用资源
		}
		PCB* temppcb = m_PCBBQueue.front();
		for (size_t j = 0; j < remain.size(); ++j)
		{
			if (remain[j] - (temppcb->needNums[j] - temppcb->disNums[j]) < 0)
			{
				return false;
			}
			changeNums[j] = temppcb->needNums[j];					//回收资源		
		}
		m_PCBBQueue.pop();
		m_PCBBQueue.push(temppcb);
	}
	return true;
}

