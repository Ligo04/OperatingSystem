#include "PCB.h"

PCB::PCB(std::string sname, int arriveTime)
	:name(sname),currStatus(Status::Wait), waitTime(0), ranTime(0),arriveTime(arriveTime)
{
	needTime = random_int(10, 20);
}

PCB::~PCB()
{
}

int random_int(int min, int max, unsigned int seed)
{
	std::default_random_engine e(static_cast<unsigned int>(seed));
	std::uniform_int_distribution<int> u(min, max);
	return u(e);
}
