#pragma once
#include<vector>
#include<queue>
#include<list>
#include"Job.h"
#include"Partition.h"
#include"RR.h"


class OperatorSystem
{
public:
	OperatorSystem(int initMemSize = 1024, int timeslice = 2);
	~OperatorSystem();
	void EnterJob(Job* job);
	void Scheduling();                              //循环中调用
	void WakeUpPCB();								//唤醒进程
	Partition* AllocMem(Job* job);					//分配内存	
	void RecycleMem(Job* job);						//回收内存
	bool IsEnd();									//是否结束
	
public:
	size_t                       m_WorkJobNum;
	std::queue<Job*>             m_AllJobs;
	std::vector<Job*>            m_Jobs;
	std::vector<JCB*>            m_Jcbs;
	std::vector<Job*>            m_FinJobs;
	std::list<Partition*>        m_ParList;
	RR*							 m_RR;
	int						     m_ParSerial;
	int						     m_Timer;
	int                          m_WakeUptime;
};

