#pragma once
#include <string>
#include "PCB.h"
#include "Partition.h"
#pragma execution_character_set("utf-8")  



struct Job
{
public:
	Job(std::string name, int size,int arrive,int need):jobName(name), requeireSize(size),arriveTime(arrive),needTime(need){}
	~Job() {};
public:
	std::string jobName;		
	int			requeireSize;
	int			arriveTime;
	int         needTime;
};

struct JCB
{
public:
	JCB(Job* job, PCB* pcb, Partition* par) :pJob(job),pPcb(pcb),pPar(par){}
	~JCB() {}
public:
	Job*          pJob;
	PCB*          pPcb;
	Partition*    pPar;
};



