#pragma once
#include <string>
#pragma execution_character_set("utf-8")  
enum class ParType
{
	Undistributed,					//未分配
	Allocated						//已分配
};

struct Partition
{
public:
	Partition(int serial,int initSize, int address = 0, ParType type= ParType::Undistributed) :parSerial(serial),size(initSize), initAddress(address),currType(type) {}
	~Partition() {};
	std::string CurrTypeToStdString()
	{
		if (currType == ParType::Undistributed)
			return std::string("未分配");
		else
		{
			return std::string("已分配");
		}
	};
public:
	int parSerial;						
	int initAddress;					
	int size;
	ParType currType;
};

