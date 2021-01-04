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
	void Scheduling();                              //ѭ���е���
	void WakeUpPCB();								//���ѽ���
	Partition* AllocMem(Job* job);					//�����ڴ�	
	void RecycleMem(Job* job);						//�����ڴ�
	bool IsEnd();									//�Ƿ����
	
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

