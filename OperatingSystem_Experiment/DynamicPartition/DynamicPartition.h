#ifndef __DYNAMIC_PARTITION
#define __DYNAMIC_PARTITION
#include <list>
#include <vector>
#include"FreePartition.h"

class DynamicPartition
{
public :
	DynamicPartition(std::vector<Job*> jobs,std::list<Partition> freelist);
	~DynamicPartition();

	void FirstPar();
	void SecondPar();

	//首次适应法
	void Alloca_First(Job* job);
	void Recycle_First(Job* job);
	void Adjust_First();
	void Show_First();
	//最佳适应法
	void Alloc_Best(Job* job);
	void Recycle_Best(Job* job);
	void Adjust_Best();
	void Show_Best();
private:
	std::vector<Job*>        m_Jobs;				//作业作业
	std::list<Partition>     m_FreePartList;		//空闲分区链
	int						 m_Count;				//作业分配次数
}; 

#endif // !__DYNAMIC_PARTITION

