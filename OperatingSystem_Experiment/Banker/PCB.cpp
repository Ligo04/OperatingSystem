#include "PCB.h"
#include <chrono>

PCB::PCB(std::string sname, std::vector<int> neednum,int arriveTime)
	:name(sname),currStatus(Status::Wait), waitTime(0), ranTime(0),arriveTime(arriveTime),needNums(neednum)
{
	needTime = random_int(10, 20);
	disNums = std::vector<int>(needNums.size(), 0);
}

PCB::~PCB()
{
	needNums.clear();
	disNums.clear();
}

bool PCB::IsCanDis(const std::vector<int> newRecourse) const
{
	for (size_t i = 0; i < newRecourse.size(); ++i)
	{
		if (disNums[i] + newRecourse[i] > needNums[i])
		{
			return false;
		}
	}
	return true;
}

bool PCB::IsSatMax(const std::vector<int> newRecourse) const
{
	for (size_t i = 0; i < newRecourse.size(); ++i)
	{
		if (disNums[i]+ newRecourse[i] != needNums[i])
		{
			return false;
		}
	}
	return true;
}

void PCB::AddResource(std::vector<int> newRecourse)
{
	for (size_t i = 0; i < newRecourse.size(); ++i)
	{
		disNums[i] += newRecourse[i];
	}
}


bool PCB::IsMaxResource()
{
	for (size_t i = 0; i < disNums.size(); ++i)
	{
		if (disNums[i] != needNums[i])
		{
			return false;
		}
	}
	return true;
}

int random_int(int min, int max)
{
	std::default_random_engine e(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<> u(min, max);
	return u(e);
}
