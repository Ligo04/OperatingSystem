
#ifndef __PCB_H
#define __PCB_H

#include<string>
#include<random>
#include<ctime>
#include<vector>

class PCB
{
public:

	enum class Status
	{
		Wait,Run,Block,Finish
	};
	PCB(std::string name, std::vector<int> neednum, int arriveTime = 0);
	~PCB();

	bool IsCanDis(const std::vector<int> newRecourse) const;			//���Խ���Դ�������
	bool IsSatMax(const std::vector<int> newRecourse) const;
	void AddResource(std::vector<int> newRecourse);
	bool IsMaxResource();
public:
	std::string name;				//������
	std::vector<int> needNums;		//������Ҫ����Դ��
	std::vector<int> disNums;		//�����ѷ������Դ��

	int arriveTime;					//���̵ĵ���ʱ��
	int waitTime;					//���̵ĵȴ�ʱ��
	int needTime;					//������Ҫ������ʱ��
	int ranTime;					//����������ʱ��
	Status currStatus;				//��������״̬
};


int random_int(int min, int max);

#endif // !__PCB_H
