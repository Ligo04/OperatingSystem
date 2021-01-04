#include "PCB.h"
#include <chrono>
PCB::PCB(std::string sname, int needtime, int arriveTime)
	:name(sname),currStatus(Status::Wait),waitTime(0), ranTime(0),arriveTime(arriveTime),needTime(needtime)
{
	
}

PCB::~PCB()
{
}

int random_int(int min, int max)
{
	std::default_random_engine e(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<> u(min, max);
	return u(e);
}