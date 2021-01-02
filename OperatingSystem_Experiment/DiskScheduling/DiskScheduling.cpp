#include "DiskScheduling.h"
#include <chrono>
#include<random>
#include<ctime>
#include <string>
#include <iostream>
#include<algorithm>
int random_int(int min, int max)
{
	std::default_random_engine e(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<> u(min, max);
	return u(e);
}

DiskScheduling::DiskScheduling(int pos, std::vector<int> diskNum)
	: m_InitPos(pos),m_DiskNumbers(diskNum)
{

}

DiskScheduling::~DiskScheduling()
{
	if (!m_DiskNumbers.empty())
		m_DiskNumbers.clear();
}

void DiskScheduling::FCFS()
{
	std::vector<int> temp;
	//先来先服务
	for (auto& p : m_DiskNumbers)
	{
		temp.push_back(p);
	}

	//计算寻道数
	int total = std::abs(m_InitPos - temp[0]);
	for (size_t i = 0; i < temp.size() - 1; i++)
	{
		total += std::abs(temp[i] - temp[i + 1]);
	}
	float avg = (float)total / temp.size();
	std::string str = "-------------------------------先来先服务算法-------------------------------\n磁盘磁头移动顺序:";
	for (auto& p : temp)
	{
		str += std::to_string(p) + " ";
	}
	str += "\n磁头的平均移动磁道数: " + std::to_string(avg) + "\n\n";
	std::cout << str;
}

void DiskScheduling::SSTF()
{
	std::vector<int> diskNum = m_DiskNumbers;
	std::vector<int> temp;
	//最短寻路
	int pos = m_InitPos;
	for (size_t i = 0; i < m_DiskNumbers.size(); ++i)
	{
		int dis = INT_MAX;
		std::vector<int>::iterator posIto;
		for (auto disk = diskNum.begin(); disk != diskNum.end(); disk++)
		{
			int d = std::abs(*disk - pos);
			if (d < dis)
			{
				dis = d;
				posIto = disk;
			}
		}
		pos = *posIto;
		temp.push_back(pos);
		diskNum.erase(posIto);
	}

	//计算寻道数
	int total = m_InitPos - temp[0];
	for (size_t i = 0; i < temp.size() - 1; i++)
	{
		total += std::abs(temp[i] - temp[i + 1]);
	}
	float avg = (float)total / temp.size();
	std::string str = "-------------------------------最短寻路算法-------------------------------\n磁盘磁头移动顺序:";
	for (auto& p : temp)
	{
		str += std::to_string(p) + " ";
	}
	str += "\n磁头的平均移动磁道数: " + std::to_string(avg) + "\n\n";
	std::cout << str;
}

void DiskScheduling::SCAN()
{
	std::sort(m_DiskNumbers.begin(), m_DiskNumbers.end(), [](int& left, int& right)->bool {return left < right; });
	std::vector<int> temp;
	//扫描算法
	size_t Ipos = 0;
	for (size_t i = 0; i < m_DiskNumbers.size() - 1; ++i)
	{
		if (m_InitPos == m_DiskNumbers[i])
		{
			Ipos = i;
			break;
		}
		else if (m_InitPos == m_DiskNumbers[i + 1])
		{
			Ipos = i + 1;
			break;
		}
		else if (m_InitPos > m_DiskNumbers[i] && m_InitPos < m_DiskNumbers[i + 1])
		{
			Ipos = i + 1;
			break;
		}
	}

	for (size_t i=Ipos; i < m_DiskNumbers.size(); ++i)
	{
		temp.push_back(m_DiskNumbers[i]);
	}
	for (int i = Ipos - 1; i >= 0; --i)
	{
		temp.push_back(m_DiskNumbers[i]);
	}

	//计算寻道数
	int total = std::abs(m_InitPos - temp[0]);
	for (size_t i = 0; i < temp.size() - 1; i++)
	{
		total += std::abs(temp[i] - temp[i + 1]);
	}
	float avg = (float)total / temp.size();
	std::string str = "-------------------------------扫描算法-------------------------------\n磁盘磁头移动顺序:";
	for (auto& p : temp)
	{
		str += std::to_string(p) + " ";
	}
	str += "\n磁头的平均移动磁道数: " + std::to_string(avg) + "\n\n";
	std::cout << str;
}

void DiskScheduling::CSCAN()
{
	std::sort(m_DiskNumbers.begin(), m_DiskNumbers.end(), [](int& left, int& right)->bool {return left < right; });
	std::vector<int> temp;
	//扫描算法
	size_t Ipos = 0;
	for (size_t i = 0; i < m_DiskNumbers.size() - 1; ++i)
	{
		if (m_InitPos == m_DiskNumbers[i])
		{
			Ipos = i;
			break;
		}
		else if (m_InitPos == m_DiskNumbers[i + 1])
		{
			Ipos = i + 1;
			break;
		}
		else if (m_InitPos > m_DiskNumbers[i] && m_InitPos < m_DiskNumbers[i + 1])
		{
			Ipos = i + 1;
			break;
		}
	}

	for (size_t i = Ipos; i < m_DiskNumbers.size(); ++i)
	{
		temp.push_back(m_DiskNumbers[i]);
	}
	for (size_t i = 0; i < Ipos; ++i)
	{
		temp.push_back(m_DiskNumbers[i]);
	}

	//计算寻道数
	int total = std::abs(m_InitPos - temp[0]);
	for (size_t i = 0; i < temp.size() - 1; i++)
	{
		total += std::abs(temp[i] - temp[i + 1]);
	}
	float avg = (float)total / temp.size();
	std::string str = "-------------------------------扫描算法-------------------------------\n磁盘磁头移动顺序:";
	for (auto& p : temp)
	{
		str += std::to_string(p) + " ";
	}
	str += "\n磁头的平均移动磁道数: " + std::to_string(avg) + "\n\n";
	std::cout << str;
}
