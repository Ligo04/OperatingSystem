#include"SJF.h"
#include"Menu.h"
#include<vector>
#include<Windows.h>

void SJFScheduling()
{
	system("cls");
	std::vector<int> arriveTime;			//����ʱ�����
	arriveTime.push_back(0);
	for (size_t i = 0; i < 4; i++)
	{
		int time = random_int(5,25,i);
		arriveTime.push_back(time);
	}
	std::sort(arriveTime.begin(), arriveTime.end(), [](int left, int right)->bool {return left < right; });

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
			break;
		}
		time++;
		Sleep(100);
	}
	delete mpSJF;
	mpSJF = nullptr;
}

int main()
{
	Menu* pmenu = Menu::Instance();
	pmenu->SetTitle("---------���̵���---------");
	std::pair <std::string, std::function<void(void)>> one("1.����ҵ����", SJFScheduling);
	pmenu->SelectionCallBack.push_back(one);
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