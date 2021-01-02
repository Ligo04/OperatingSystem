#include "DynamicPartition.h"
#include <iostream>
#include <Windows.h>

DynamicPartition::DynamicPartition(std::vector<Job*> jobs, std::list<Partition> freelist)
	:m_Jobs(jobs),m_FreePartList(freelist),m_Count(0)
{
}

DynamicPartition::~DynamicPartition()
{
	if (!m_FreePartList.empty())
		m_FreePartList.clear();
	if (!m_Jobs.empty())
		m_Jobs.clear();
}

void DynamicPartition::FirstPar()
{
	//��ҵ1����
	Alloca_First(m_Jobs[0]);
	Sleep(100);
	//��ҵ2����
	Alloca_First(m_Jobs[1]);
	Sleep(100);
	//��ҵ3����
	Alloca_First(m_Jobs[2]);
	Sleep(100);
	//��ҵ2�ͷ�
	Recycle_First(m_Jobs[1]);
	Sleep(100);
	//��ҵ4����
	Alloca_First(m_Jobs[3]);
	Sleep(100);
	//��ҵ3�ͷ�
	Recycle_First(m_Jobs[2]);
	Sleep(100);
	//��ҵ1�ͷ�
	Recycle_First(m_Jobs[0]);
	Sleep(100);
	//��ҵ5����
	Alloca_First(m_Jobs[4]);
	Sleep(100);
	//��ҵ6����
	Alloca_First(m_Jobs[5]);
	Sleep(100);
	//��ҵ7����
	Alloca_First(m_Jobs[6]);
	Sleep(100);
	//��ҵ8����
	Alloca_First(m_Jobs[7]);
	Sleep(100);
}

void DynamicPartition::SecondPar()
{
	//��ҵ1����
	Alloc_Best(m_Jobs[0]);
	Sleep(100);
	//��ҵ2����
	Alloc_Best(m_Jobs[1]);
	Sleep(100);
	//��ҵ3����
	Alloc_Best(m_Jobs[2]);
	Sleep(100);
	//��ҵ2�ͷ�
	Recycle_Best(m_Jobs[1]);
	Sleep(100);
	//��ҵ4����
	Alloc_Best(m_Jobs[3]);
	Sleep(100);
	//��ҵ3�ͷ�
	Recycle_Best(m_Jobs[2]);
	Sleep(100);
	//��ҵ1�ͷ�
	Recycle_Best(m_Jobs[0]);
	Sleep(100);
	//��ҵ5����
	Alloc_Best(m_Jobs[4]);
	Sleep(100);
	//��ҵ6����
	Alloc_Best(m_Jobs[5]);
	Sleep(100);
	//��ҵ7����
	Alloc_Best(m_Jobs[6]);
	Sleep(100);
	//��ҵ8����
	Alloc_Best(m_Jobs[7]);
	Sleep(100);
}

void DynamicPartition::Alloca_First(Job* job)
{
	bool flag = false;
	//����
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		if (par->m_Size >= job->memSize)
		{
			par->m_Size -= job->memSize;
			job->initAdd = par->m_InitAddress;
			job->jobType = JobMemType::Allocated;
			if (par->m_Size == 0)
			{
				m_FreePartList.erase(par);
				flag = true;
				break;
			}
			par->m_InitAddress += job->memSize;
			flag = true;
			break;
		}
	}
	Adjust_First();
	Show_First();
	if (!flag)
	{

		std::cout << "�ڴ治�㣬�޷����䡣\n";
	}
}

void DynamicPartition::Recycle_First(Job* job)
{
	Partition par(job->initAdd, job->memSize);
	job->jobType = JobMemType::Undistributed;
	m_FreePartList.push_back(par);
	Adjust_First();
	Show_First();
}

void DynamicPartition::Adjust_First()
{
	m_FreePartList.sort([](Partition& par1, Partition& par2)->bool {return  par1.m_InitAddress < par2.m_InitAddress; });
}

void DynamicPartition::Show_First()
{
	std::string str = "---------------------------------��" + std::to_string(m_Count++)+"����ҵ�������---------------------------------\n";
	std::string jobstr = "��ҵ���������\n";
	std::string parstr = "���з��������\n";
	for (auto& j : m_Jobs)
	{
		jobstr += j->jobName + ": "+std::to_string(j->memSize)+"  ";
		if (j->jobType == JobMemType::Allocated)
			jobstr += "�ѷ��� \n\n";
		else
			jobstr += "δ���� \n\n";
	}
	int i = 1;
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		parstr += "������" + std::to_string(i++) + ": ";
		parstr += "��ʼ��ַ��" + std::to_string(par->m_InitAddress) + "KB  ";
		parstr += "��С�� " + std::to_string(par->m_Size) + "KB\n\n";
	}
	std::cout << str << jobstr << parstr;
}

void DynamicPartition::Alloc_Best(Job* job)
{
	bool flag = false;
	//����
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		if (par->m_Size >= job->memSize)
		{
			par->m_Size -= job->memSize;
			job->initAdd = par->m_InitAddress;
			job->jobType = JobMemType::Allocated;
			if (par->m_Size == 0)
			{
				m_FreePartList.erase(par);
				flag = true;
				break;
			}
			par->m_InitAddress += job->memSize;
			flag = true;
			break;
		}
	}
	Adjust_Best();
	Show_Best();
	if (!flag)
	{

		std::cout << "�ڴ治�㣬�޷����䡣\n";
	}
}

void DynamicPartition::Recycle_Best(Job* job)
{
	Partition par(job->initAdd, job->memSize);
	job->jobType = JobMemType::Undistributed;
	m_FreePartList.push_back(par);
	Adjust_Best();
	Show_Best();
}

void DynamicPartition::Adjust_Best()
{
	m_FreePartList.sort([](Partition& par1, Partition& par2)->bool {return  par1.m_Size < par2.m_Size; });
}

void DynamicPartition::Show_Best()
{
	std::string str = "---------------------------------��" + std::to_string(m_Count++) + "����ҵ�������---------------------------------\n";
	std::string jobstr = "��ҵ���������\n";
	std::string parstr = "���з��������\n";
	for (auto& j : m_Jobs)
	{
		jobstr += j->jobName + ": " + std::to_string(j->memSize) + "  ";
		if (j->jobType == JobMemType::Allocated)
			jobstr += "�ѷ��� \n\n";
		else
			jobstr += "δ���� \n\n";
	}
	int i = 1;
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		parstr += "������" + std::to_string(i++) + ": ";
		parstr += "��ʼ��ַ��" + std::to_string(par->m_InitAddress) + "KB  ";
		parstr += "��С�� " + std::to_string(par->m_Size) + "KB\n\n";
	}
	std::cout << str << jobstr << parstr;
}


