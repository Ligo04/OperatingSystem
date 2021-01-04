
#ifndef __PCB_H
#define __PCB_H

#include<string>
#include<random>
#include<ctime>

class PCB
{
public:

	enum class Status
	{
		Wait,Run,Finish
	};
	PCB(std::string sname,int needtime,int arriveTime=0);
	~PCB();

public:
	std::string name;		//进程名
	int arriveTime;			//进程的到达时间
	int waitTime;			//进程的等待时间
	int needTime;			//进程需要的运行时间
	int ranTime;			//进程已运行时间
	Status currStatus;		//进程运行状态
};


int random_int(int min, int max);

#endif // !__PCB_H
