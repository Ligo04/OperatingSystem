#include "Banker.h"
#include "Menu.h"
#include<Windows.h>

void BankerScheDul()
{
	std::vector<int> res{ 10,15,12 };
	Banker* mpBanker = new Banker(res);
	for (int i = 0; i < 5; ++i)
	{
		std::vector<int> needNum;
		for (size_t i = 0; i < res.size(); ++i)
		{
			int num = random_int(1, res[i]/2);
			needNum.push_back(num);
		}
		PCB* pcb = new PCB("进程" + std::to_string(i), needNum);
		mpBanker->Enter(pcb);
	}
	while (true)
	{
		mpBanker->Scheuduled();
		if (mpBanker->IsEnd())
		{
			break;
		}
		Sleep(100);
	}
}


int main()
{
	Menu* pmenu = Menu::Instance();
	pmenu->SetTitle("-----------------------------银行家算法-----------------------------");
	std::pair<std::string, std::function<void(void)>> one("按1进行调度", BankerScheDul);
	pmenu->SelectionCallBack.push_back(one);
	while (true)
	{
		pmenu->Display();
		pmenu->GetInput();
		system("cls");
		pmenu->HandleInput();
		system("pause");
		system("cls");
	}
	return 0;
}