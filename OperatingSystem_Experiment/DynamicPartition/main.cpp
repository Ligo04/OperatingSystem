#include "DynamicPartition.h"
#include "Menu.h"
#include <vector>
#include <iostream>

void FirstPar()
{
	std::cout << "------------------------�״���Ӧ�㷨------------------------" << std::endl;
	std::vector<Job*> jobs;
	Job* job1 = new Job("��ҵ1", 130);
	jobs.push_back(job1);
	Job* job2 = new Job("��ҵ2", 60);
	jobs.push_back(job2);
	Job* job3 = new Job("��ҵ3", 100);
	jobs.push_back(job3);
	Job* job4 = new Job("��ҵ4", 200);
	jobs.push_back(job4);
	Job* job5 = new Job("��ҵ5", 140);
	jobs.push_back(job5);
	Job* job6 = new Job("��ҵ6", 60);
	jobs.push_back(job6);
	Job* job7 = new Job("��ҵ7", 50);
	jobs.push_back(job7);
	Job* job8 = new Job("��ҵ8", 60);
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
	std::cout << "------------------------�����Ӧ�㷨------------------------" << std::endl;
	std::vector<Job*> jobs;
	Job* job1 = new Job("��ҵ1", 130);
	jobs.push_back(job1);
	Job* job2 = new Job("��ҵ2", 60);
	jobs.push_back(job2);
	Job* job3 = new Job("��ҵ3", 100);
	jobs.push_back(job3);
	Job* job4 = new Job("��ҵ4", 200);
	jobs.push_back(job4);
	Job* job5 = new Job("��ҵ5", 140);
	jobs.push_back(job5);
	Job* job6 = new Job("��ҵ6", 60);
	jobs.push_back(job6);
	Job* job7 = new Job("��ҵ7", 50);
	jobs.push_back(job7);
	Job* job8 = new Job("��ҵ8", 60);
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
	pmenu->SetTitle("------------------------��̬�������䷽ʽ��ģ��------------------------");
	std::pair<std::string, std::function<void(void)>>  one("1.�״���Ӧ�㷨", FirstPar);
	std::pair<std::string, std::function<void(void)>>  tow("2.�����Ӧ�㷨", SecondPar);
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