#include"SJF.h"
#include"RR.h"
#include"HRRN.h"
#include"Menu.h"
#include<vector>
#include<Windows.h>


std::vector<PCB*> Initpcbs;

void Init()
{
	PCB* pcb = new PCB("����" + std::to_string(0), 0);
	Initpcbs.push_back(pcb);
	for (size_t i = 0; i < 4; i++)
	{
		int time = random_int(5, 25);

		PCB* pcb = new PCB("����" + std::to_string(i+1), time);
		Initpcbs.push_back(pcb);
	}
	std::sort(Initpcbs.begin(), Initpcbs.end(), [](PCB* left, PCB* right)->bool {return left->arriveTime < right->arriveTime; });
}

void SJFScheduling()
{
	system("cls");
	std::vector<PCB*> pcbs = Initpcbs;
	int time = 0;
	SJF* mpSJF = new SJF();
	while (true)
	{
		while (pcbs.size() != 0 && time == pcbs.front()->arriveTime)
		{
			//��������
			mpSJF->Enter(*pcbs.front());
			pcbs.erase(pcbs.begin());
		}
		mpSJF->Scheuduled();
		if (mpSJF->IsEnd() && pcbs.size() == 0)
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
	std::vector<PCB*> pcbs = Initpcbs;
	int num = 0;
	int time = 0;
	RR* mpRR = new RR();
	while (true)
	{
		while (pcbs.size() != 0 && time == pcbs.front()->arriveTime)
		{
			//��������
			mpRR->Enter(pcbs.front());
			pcbs.erase(pcbs.begin());
		}
		mpRR->Scheuduled();
		if (mpRR->IsEnd() && pcbs.size() == 0)
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
	std::vector<PCB*> pcbs = Initpcbs;
	int num = 0;
	int time = 0;
	HRRN* mpHRRN = new HRRN();
	while (true)
	{
		while (pcbs.size() != 0 && time == pcbs.front()->arriveTime)
		{
			//��������
			mpHRRN->Enter(*pcbs.front());
			pcbs.erase(pcbs.begin());
		}
		mpHRRN->Scheuduled();
		if (mpHRRN->IsEnd() && pcbs.size() == 0)
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