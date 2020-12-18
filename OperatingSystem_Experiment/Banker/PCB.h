
#ifndef __PCB_H
#define __PCB_H

#include<string>
#include<random>
#include<ctime>
#include<vector>

class PCB
{
public:

	enum class Status
	{
		Wait,Run,Block,Finish
	};
	PCB(std::string name, std::vector<int> neednum, int arriveTime = 0);
	~PCB();

	bool IsCanDis(const std::vector<int> newRecourse) const;			//可以将资源分配给其
	bool IsSatMax(const std::vector<int> newRecourse) const;
	void AddResource(std::vector<int> newRecourse);
	bool IsMaxResource();
public:
	std::string name;				//进程名
	std::vector<int> needNums;		//进程需要的资源数
	std::vector<int> disNums;		//进程已分配的资源数

	int arriveTime;					//进程的到达时间
	int waitTime;					//进程的等待时间
	int needTime;					//进程需要的运行时间
	int ranTime;					//进程已运行时间
	Status currStatus;				//进程运行状态
};


int random_int(int min, int max);

#endif // !__PCB_H
