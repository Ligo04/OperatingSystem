
#ifndef __PCB_H
#define __PCB_H

#include<string>
#include<random>
#include<ctime>

class PCB
{
public:

	enum class Status
	{
		Wait,Run,Finish
	};
	PCB(std::string name,int arriveTime=0);
	~PCB();

public:
	std::string name;		//������
	int arriveTime;			//���̵ĵ���ʱ��
	int waitTime;			//���̵ĵȴ�ʱ��
	int needTime;			//������Ҫ������ʱ��
	int ranTime;			//����������ʱ��
	Status currStatus;		//��������״̬
};


int random_int(int min, int max, unsigned int seed = time(nullptr));

#endif // !__PCB_H
