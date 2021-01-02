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

	//�״���Ӧ��
	void Alloca_First(Job* job);
	void Recycle_First(Job* job);
	void Adjust_First();
	void Show_First();
	//�����Ӧ��
	void Alloc_Best(Job* job);
	void Recycle_Best(Job* job);
	void Adjust_Best();
	void Show_Best();
private:
	std::vector<Job*>        m_Jobs;				//��ҵ��ҵ
	std::list<Partition>     m_FreePartList;		//���з�����
	int						 m_Count;				//��ҵ�������
}; 

#endif // !__DYNAMIC_PARTITION

