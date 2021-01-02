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
	//作业1申请
	Alloca_First(m_Jobs[0]);
	Sleep(100);
	//作业2申请
	Alloca_First(m_Jobs[1]);
	Sleep(100);
	//作业3申请
	Alloca_First(m_Jobs[2]);
	Sleep(100);
	//作业2释放
	Recycle_First(m_Jobs[1]);
	Sleep(100);
	//作业4申请
	Alloca_First(m_Jobs[3]);
	Sleep(100);
	//作业3释放
	Recycle_First(m_Jobs[2]);
	Sleep(100);
	//作业1释放
	Recycle_First(m_Jobs[0]);
	Sleep(100);
	//作业5申请
	Alloca_First(m_Jobs[4]);
	Sleep(100);
	//作业6申请
	Alloca_First(m_Jobs[5]);
	Sleep(100);
	//作业7申请
	Alloca_First(m_Jobs[6]);
	Sleep(100);
	//作业8申请
	Alloca_First(m_Jobs[7]);
	Sleep(100);
}

void DynamicPartition::SecondPar()
{
	//作业1申请
	Alloc_Best(m_Jobs[0]);
	Sleep(100);
	//作业2申请
	Alloc_Best(m_Jobs[1]);
	Sleep(100);
	//作业3申请
	Alloc_Best(m_Jobs[2]);
	Sleep(100);
	//作业2释放
	Recycle_Best(m_Jobs[1]);
	Sleep(100);
	//作业4申请
	Alloc_Best(m_Jobs[3]);
	Sleep(100);
	//作业3释放
	Recycle_Best(m_Jobs[2]);
	Sleep(100);
	//作业1释放
	Recycle_Best(m_Jobs[0]);
	Sleep(100);
	//作业5申请
	Alloc_Best(m_Jobs[4]);
	Sleep(100);
	//作业6申请
	Alloc_Best(m_Jobs[5]);
	Sleep(100);
	//作业7申请
	Alloc_Best(m_Jobs[6]);
	Sleep(100);
	//作业8申请
	Alloc_Best(m_Jobs[7]);
	Sleep(100);
}

void DynamicPartition::Alloca_First(Job* job)
{
	bool flag = false;
	//分配
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

		std::cout << "内存不足，无法分配。\n";
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
	std::string str = "---------------------------------第" + std::to_string(m_Count++)+"次作业分配情况---------------------------------\n";
	std::string jobstr = "作业分配情况：\n";
	std::string parstr = "空闲分区情况：\n";
	for (auto& j : m_Jobs)
	{
		jobstr += j->jobName + ": "+std::to_string(j->memSize)+"  ";
		if (j->jobType == JobMemType::Allocated)
			jobstr += "已分配 \n\n";
		else
			jobstr += "未分配 \n\n";
	}
	int i = 1;
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		parstr += "空闲区" + std::to_string(i++) + ": ";
		parstr += "起始地址：" + std::to_string(par->m_InitAddress) + "KB  ";
		parstr += "大小： " + std::to_string(par->m_Size) + "KB\n\n";
	}
	std::cout << str << jobstr << parstr;
}

void DynamicPartition::Alloc_Best(Job* job)
{
	bool flag = false;
	//分配
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

		std::cout << "内存不足，无法分配。\n";
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
	std::string str = "---------------------------------第" + std::to_string(m_Count++) + "次作业分配情况---------------------------------\n";
	std::string jobstr = "作业分配情况：\n";
	std::string parstr = "空闲分区情况：\n";
	for (auto& j : m_Jobs)
	{
		jobstr += j->jobName + ": " + std::to_string(j->memSize) + "  ";
		if (j->jobType == JobMemType::Allocated)
			jobstr += "已分配 \n\n";
		else
			jobstr += "未分配 \n\n";
	}
	int i = 1;
	for (auto par = m_FreePartList.begin(); par != m_FreePartList.end(); ++par)
	{
		parstr += "空闲区" + std::to_string(i++) + ": ";
		parstr += "起始地址：" + std::to_string(par->m_InitAddress) + "KB  ";
		parstr += "大小： " + std::to_string(par->m_Size) + "KB\n\n";
	}
	std::cout << str << jobstr << parstr;
}


