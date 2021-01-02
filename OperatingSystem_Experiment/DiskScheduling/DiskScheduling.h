#ifndef __DISK_SCHEDULING
#define __DISK_SCHEDULING
#include <vector>
class DiskScheduling
{
public:
	DiskScheduling(int pos,std::vector<int> diskNum);
	~DiskScheduling();

	//先来先服务
	void FCFS();
	//最短寻路
	void SSTF();
	//扫描算法
	void SCAN();
	//循环扫描算法
	void CSCAN();
private:
	std::vector<int> m_DiskNumbers;	  //磁盘请求
	int				 m_InitPos;		  //初始磁盘位置	
};

int random_int(int min, int max);
#endif // !__DISK_SCHEDULING
