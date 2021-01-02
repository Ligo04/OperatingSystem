#include "DynamicPartition.h"
#include "Menu.h"
#include <vector>
#include <iostream>

void FirstPar()
{
	std::cout << "------------------------首次适应算法------------------------" << std::endl;
	std::vector<Job*> jobs;
	Job* job1 = new Job("作业1", 130);
	jobs.push_back(job1);
	Job* job2 = new Job("作业2", 60);
	jobs.push_back(job2);
	Job* job3 = new Job("作业3", 100);
	jobs.push_back(job3);
	Job* job4 = new Job("作业4", 200);
	jobs.push_back(job4);
	Job* job5 = new Job("作业5", 140);
	jobs.push_back(job5);
	Job* job6 = new Job("作业6", 60);
	jobs.push_back(job6);
	Job* job7 = new Job("作业7", 50);
	jobs.push_back(job7);
	Job* job8 = new Job("作业8", 60);
	jobs.push_back(job8);

	std::list<Partition> parlists;
	parlists.push_back(Partition(0, 640));
	DynamicPartition* DyPar = new DynamicPartition(jobs, parlists);
	DyPar->FirstPar();
	delete DyPar;
	DyPar = nullptr;
}
void SecondPar()
{
	std::cout << "------------------------最佳适应算法------------------------" << std::endl;
	std::vector<Job*> jobs;
	Job* job1 = new Job("作业1", 130);
	jobs.push_back(job1);
	Job* job2 = new Job("作业2", 60);
	jobs.push_back(job2);
	Job* job3 = new Job("作业3", 100);
	jobs.push_back(job3);
	Job* job4 = new Job("作业4", 200);
	jobs.push_back(job4);
	Job* job5 = new Job("作业5", 140);
	jobs.push_back(job5);
	Job* job6 = new Job("作业6", 60);
	jobs.push_back(job6);
	Job* job7 = new Job("作业7", 50);
	jobs.push_back(job7);
	Job* job8 = new Job("作业8", 60);
	jobs.push_back(job8);

	std::list<Partition> parlists;
	parlists.push_back(Partition(0, 640));
	DynamicPartition* DyPar = new DynamicPartition(jobs, parlists);
	DyPar->SecondPar();
	delete DyPar;
	DyPar = nullptr;
}

int main()
{

	Menu* pmenu = Menu::Instance();
	pmenu->SetTitle("------------------------动态分区分配方式的模拟------------------------");
	std::pair<std::string, std::function<void(void)>>  one("1.首次适应算法", FirstPar);
	std::pair<std::string, std::function<void(void)>>  tow("2.最佳适应算法", SecondPar);
	pmenu->SelectionCallBack.push_back(one);
	pmenu->SelectionCallBack.push_back(tow);
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