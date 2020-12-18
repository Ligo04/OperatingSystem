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
			//���Ƚ���
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
				std::vector<int> res = GetResources();				//������Դ
				while (!currPCB->IsCanDis(res))						//�ж��Ƿ��������
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
					//��ȫ
					if (currPCB->IsMaxResource())
					{
						//�ﵽ�������
						currPCB->ranTime++;
						currPCB->currStatus = PCB::Status::Finish;
						this->m_PCBFQueue.push(currPCB);
						ReturnResoureces(currPCB->disNums);
						currPCB = nullptr;
						m_CurrSilce = 0;
					}
					else
					{
						//û�ﵽ�������
						currPCB->ranTime++;
					}
					Show();
					break;
				}
				else
				{
					//����ȫ
					currPCB->currStatus = PCB::Status::Block;			//����
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
	
	std::string str = "-------------------------��" + std::to_string(m_ScheCount++) + "�ε���-------------------------\n";
	std::string runstr = "---------�������еĽ���---------\n";
	std::string waitstr = "---------�������еĽ���---------\n";
	std::string blockstr = "---------�������еĽ���---------\n";
	std::string finishstr = "---------��ɵĽ���---------\n";

	if (currPCB != nullptr)
	{
		runstr += "����" + currPCB->name + ":{\n";
		runstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(currPCB->waitTime) + "\n";
		runstr += "    ����������ʱ�䣺" + std::to_string(currPCB->ranTime) + "\n";
		runstr += "    ���̵�����Ҫ����Դ����";
		for (auto& num : currPCB->needNums)
		{
			runstr += std::to_string(num) + "  ";
		}
		runstr += "\n";
		runstr += "    ���̵��ѷ������Դ����";
		for (auto& num : currPCB->disNums)
		{
			runstr += std::to_string(num) + "  ";
		}
		runstr += "\n}\n\n";
	}

	for(size_t i=0;i<m_PCBQueue.size();++i)
	{
		PCB* p = m_PCBQueue.front();

		waitstr += "����" + p->name + ":{\n";
		waitstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p->waitTime) + "\n";
		waitstr += "    ����������ʱ�䣺" + std::to_string(p->ranTime) + "\n";
		waitstr += "    ���̵�����Ҫ����Դ����";
		for (auto& num : p->needNums)
		{
			waitstr += std::to_string(num) + "  ";
		}
		waitstr += "\n";
		waitstr += "    ���̵��ѷ������Դ����";
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

		blockstr += "����" + p->name + ":{\n";
		blockstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p->waitTime) + "\n";
		blockstr += "    ����������ʱ�䣺" + std::to_string(p->ranTime) + "\n";
		blockstr += "    ���̵�����Ҫ����Դ����";
		for (auto& num : p->needNums)
		{
			blockstr += std::to_string(num) + "  ";
		}
		blockstr += "\n";
		blockstr += "    ���̵��ѷ������Դ����";
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

		finishstr += "����" + p->name + ":{\n";
		finishstr += "    ���̵ĵȴ�ʱ�䣺" + std::to_string(p->waitTime) + "\n";
		finishstr += "    ����������ʱ�䣺" + std::to_string(p->ranTime) + "\n";
		finishstr += "    ���̵�����Ҫ����Դ����";
		for (auto& num : p->needNums)
		{
			finishstr += std::to_string(num) + "  ";
		}
		finishstr += "\n";
		finishstr += "    ���̵��ѷ������Դ����";
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
	//���ж��Ƿ��������ʣ����Դ�ܲ�����η���
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
		changeNums[i] += currPCB->needNums[i];						//������Դ
	}

	for (size_t i = 0; i < m_PCBQueue.size(); ++i)
	{
		for (size_t j = 0; j < remain.size(); ++j)
		{
			remain[j] = remain[j] + changeNums[j];					//����ʣ�������Դ
		}
		PCB* temppcb = m_PCBQueue.front();
		for (size_t j = 0; j < remain.size(); ++j)
		{
			if (remain[j] - (temppcb->needNums[j] - temppcb->disNums[j]) < 0)
			{
				return false;
			}
			changeNums[j] = temppcb->needNums[j];					//������Դ		
		}
		m_PCBQueue.pop();
		m_PCBQueue.push(temppcb);
	}

	for (size_t i = 0; i < m_PCBBQueue.size(); ++i)
	{
		for (size_t j = 0; j < remain.size(); ++j)
		{
			remain[j] = remain[j] + changeNums[j];					//����ʣ�������Դ
		}
		PCB* temppcb = m_PCBBQueue.front();
		for (size_t j = 0; j < remain.size(); ++j)
		{
			if (remain[j] - (temppcb->needNums[j] - temppcb->disNums[j]) < 0)
			{
				return false;
			}
			changeNums[j] = temppcb->needNums[j];					//������Դ		
		}
		m_PCBBQueue.pop();
		m_PCBBQueue.push(temppcb);
	}
	return true;
}

