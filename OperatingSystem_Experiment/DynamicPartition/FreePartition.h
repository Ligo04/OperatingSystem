#ifndef __FREEPATITION
#define __FREEPATITION
#include<string>


enum class JobMemType
{
	Undistributed,					//未分配
	Allocated						//已分配
};

struct Job
{
	Job(std::string name,int size):jobName(jobName),memSize(size),jobType(JobMemType::Undistributed),initAdd(0){}
	~Job() {}
	std::string jobName;			
	JobMemType  jobType;
	int initAdd;			
	int memSize;
};

struct Partition
{
public: 
	Partition(int initaddress,int size) :m_InitAddress(initaddress),m_Size(size) {}
	~Partition() {}
public:
	int m_InitAddress;				//起始地址
	int m_Size;						//分区大小(KB)
}; 
#endif // !__FREEPATITION

