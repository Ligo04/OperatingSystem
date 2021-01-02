#include"SJF.h"
#include"RR.h"
#include"HRRN.h"
#include"Menu.h"
#include<vector>
#include<Windows.h>


std::vector<int> InitarriveTime;			//����ʱ�����

void Init()
{
	InitarriveTime.push_back(0);
	for (size_t i = 0; i < 4; i++)
	{
		int time = random_int(5, 25);
		InitarriveTime.push_back(time);
	}
	std::sort(InitarriveTime.begin(), InitarriveTime.end(), [](int left, int right)->bool {return left < right; });
}

void SJFScheduling()
{
	system("cls");
	std::vector<int> arriveTime = InitarriveTime;
	int num = 0;
	int time = 0;
	SJF* mpSJF = new SJF();
	while (true)
	{
		if (arriveTime.size() != 0 && time == arriveTime.front())
		{
			//��������
			PCB pcb("����" + std::to_string(num++),arriveTime.front());
			mpSJF->Enter(pcb);
			arriveTime.erase(arriveTime.begin());
		}
		mpSJF->Scheuduled();
		if (mpSJF->IsEnd() && arriveTime.size() == 0)
		{
			mpSJF->ShowTime();
			break;
		}
		time++;
		Sleep(100);
	}
	delete mpSJF;
	mpSJF = nullptr;
}

void RRScheduling()
{
	system("cls");
	std::vector<int> arriveTime = InitarriveTime;
	int num = 0;
	int time = 0;
	RR* mpRR = new RR();
	while (true)
	{
		if (arriveTime.size() != 0 && time == arriveTime.front())
		{
			//��������
			PCB* pcb=new PCB("����" + std::to_string(num++), arriveTime.front());
			mpRR->Enter(pcb);
			arriveTime.erase(arriveTime.begin());
		}
		mpRR->Scheuduled();
		if (mpRR->IsEnd() && arriveTime.size() == 0)
		{
			mpRR->ShowTime();
			break;
		}
		time++;
		Sleep(100);
	}
	delete mpRR;
	mpRR = nullptr;
}

void HRRNScheduling()
{
	system("cls");
	std::vector<int> arriveTime = InitarriveTime;
	int num = 0;
	int time = 0;
	HRRN* mpHRRN = new HRRN();
	while (true)
	{
		if (arriveTime.size() != 0 && time == arriveTime.front())
		{
			//��������
			PCB pcb("����" + std::to_string(num++), arriveTime.front());
			mpHRRN->Enter(pcb);
			arriveTime.erase(arriveTime.begin());
		}
		mpHRRN->Scheuduled();
		if (mpHRRN->IsEnd() && arriveTime.size() == 0)
		{
			mpHRRN->ShowTime();
			break;
		}
		time++;
		Sleep(100);
	}
	delete mpHRRN;
	mpHRRN = nullptr;
}

int main()
{
	Init();
	Menu* pmenu = Menu::Instance();
	pmenu->SetTitle("---------���̵���---------");
	std::pair <std::string, std::function<void(void)>> one("1.����ҵ����", SJFScheduling);
	std::pair <std::string, std::function<void(void)>> two("2.ʱ��Ƭ��ת", RRScheduling);
	std::pair <std::string, std::function<void(void)>> three("3.����Ӧ������", HRRNScheduling);
	pmenu->SelectionCallBack.push_back(one);
	pmenu->SelectionCallBack.push_back(two);
	pmenu->SelectionCallBack.push_back(three);
	while (true)
	{
		pmenu->Display();
		pmenu->GetInput();
		pmenu->HandleInput();
		system("pause");
		system("cls");
	}
	return 0;
}