#include "DiskScheduling.h"
#include "Menu.h"

std::vector<int> requset;

void Init()
{
	for (size_t i = 0; i < 10; ++i)
	{
		int num = random_int(1, 200);
		requset.push_back(num);
	}
}

void FCFS()
{
	DiskScheduling* pDisk = new DiskScheduling(100,requset);
	pDisk->FCFS();
	delete pDisk;
	pDisk = nullptr;
}

void SSTF()
{
	DiskScheduling* pDisk = new DiskScheduling(100, requset);
	pDisk->SSTF();
	delete pDisk;
	pDisk = nullptr;
}

void SCAN()
{
	DiskScheduling* pDisk = new DiskScheduling(100, requset);
	pDisk->SCAN();
	delete pDisk;
	pDisk = nullptr;
}

void CSCAN()
{
	DiskScheduling* pDisk = new DiskScheduling(100, requset);
	pDisk->CSCAN();
	delete pDisk;
	pDisk = nullptr;
}

int main()
{
	Init();
	Menu* pmenu = Menu::Instance();
	pmenu->SetTitle("-------------------------------磁盘调度-------------------------------");
	std::pair<std::string, std::function<void(void)>> one("1.先来先服务算法", FCFS);
	std::pair<std::string, std::function<void(void)>> two("2.最短寻道时间优先算法", SSTF);
	std::pair<std::string, std::function<void(void)>> three("3.扫描(SCAN)算法", SCAN);
	std::pair<std::string, std::function<void(void)>> four("4.循环扫描(CSCAN)算法", CSCAN);
	pmenu->SelectionCallBack.push_back(one);
	pmenu->SelectionCallBack.push_back(two);
	pmenu->SelectionCallBack.push_back(three);
	pmenu->SelectionCallBack.push_back(four);
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