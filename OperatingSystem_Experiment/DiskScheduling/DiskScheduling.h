#ifndef __DISK_SCHEDULING
#define __DISK_SCHEDULING
#include <vector>
class DiskScheduling
{
public:
	DiskScheduling(int pos,std::vector<int> diskNum);
	~DiskScheduling();

	//�����ȷ���
	void FCFS();
	//���Ѱ·
	void SSTF();
	//ɨ���㷨
	void SCAN();
	//ѭ��ɨ���㷨
	void CSCAN();
private:
	std::vector<int> m_DiskNumbers;	  //��������
	int				 m_InitPos;		  //��ʼ����λ��	
};

int random_int(int min, int max);
#endif // !__DISK_SCHEDULING
