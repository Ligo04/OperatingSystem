#include "OperatorSystem.h"

OperatorSystem::OperatorSystem(int initMemSize, int timeslice)
	:m_WorkJobNum(5),
	m_AllJobs(std::queue<Job*>()),
	m_Jobs(std::vector<Job*>()),
	m_FinJobs(std::vector<Job*>()),
	m_ParSerial(0),
	m_Timer(0)
{
	m_ParList = std::list<Partition*>();
	Partition* initPar =new Partition(m_ParSerial++, initMemSize);
	m_ParList.push_back(initPar);
	m_RR = new RR(timeslice);
	m_WakeUptime = random_int(1, 20);
}

OperatorSystem::~OperatorSystem()
{
	if (!m_AllJobs.empty())
	{
		Job* temp = m_AllJobs.front();
		m_AllJobs.pop();
		delete temp;
		temp = nullptr;
	}

	if (!m_Jobs.empty())
	{
		m_Jobs.clear();
		m_Jobs.swap(std::vector<Job*>());
	}
	if (!m_FinJobs.empty())
	{
		m_FinJobs.clear();
		m_FinJobs.swap(std::vector<Job*>());
	}
		
	if (!m_ParList.empty())
	{
		m_ParList.clear();
		m_ParList.swap(std::list<Partition*>());
	}
	if (m_RR != nullptr)
	{
		delete m_RR;
		m_RR = nullptr;
	}
}

void OperatorSystem::EnterJob(Job* job)
{
	//�����ȷ���
	m_AllJobs.push(job);
}

void OperatorSystem::Scheduling()
{
	while (m_Jobs.size() < m_WorkJobNum && !m_AllJobs.empty())
	{
		//�����ڴ�
		Job* temp = m_AllJobs.front();
		m_AllJobs.pop();
		Partition* par = AllocMem(temp);
		if (par != nullptr)
		{
			//����ɹ�
			m_Jobs.push_back(temp);
			//����PCB
			PCB* pcb = new PCB("����-" + temp->jobName, temp->needTime);
			m_RR->Enter(pcb);
			//����JCB
			JCB* jcb = new JCB(temp, pcb, par);
			m_Jcbs.push_back(jcb);
		}
		//�ڴ治��,������
	}

	//ʱ��Ƭ��ת����
	m_RR->Scheuduled();
	//���ڻ��ѽ���
	WakeUpPCB();
	//�н������
	while (!m_RR->m_PCBFQueue.empty())
	{
		PCB* pcb = m_RR->m_PCBFQueue.front();
		std::vector<JCB*>::iterator it_JCB;
		//�ҵ���Ӧ��jcb
		for (auto jcb = m_Jcbs.begin(); jcb != m_Jcbs.end(); jcb++)
		{
			if ((*jcb)->pPcb == pcb)
			{
				it_JCB = jcb;
			}
		}
		if (*it_JCB != nullptr)
		{
			//�����ڴ�
			RecycleMem((*it_JCB)->pJob);
			//���������ҵ����
			m_FinJobs.push_back((*it_JCB)->pJob);
			//�Ƴ���������
			for (auto j = m_Jobs.begin(); j != m_Jobs.end(); j++)
			{
				if (*j == (*it_JCB)->pJob)
				{
					m_Jobs.erase(j);
					break;
				}
			}
				
			//����jcb
			m_Jcbs.erase(it_JCB);
		}
		m_RR->m_PCBFQueue.pop();
	}
}

void OperatorSystem::WakeUpPCB()
{
	if (!m_RR->m_PCBBlockQueue.empty())
	{
		if (m_Timer == m_WakeUptime)
		{
			//���ѽ���
			PCB* pcb = m_RR->m_PCBBlockQueue.front();
			m_RR->m_PCBBlockQueue.pop();
			m_RR->m_PCBQueue.push(pcb);
			m_Timer = 0;
			m_WakeUptime = random_int(1, 20);
		}
		else
		{
			m_Timer++;
		}
	}
}

Partition* OperatorSystem::AllocMem(Job* job)
{
	//�״���Ӧ
	Partition* allocPar = nullptr;
	for (auto& p : m_ParList)
	{
		if (p->currType==ParType::Undistributed && p->size >= job->requeireSize)
		{
			p->size -= job->requeireSize;
			if (p->size == 0)
			{
				p->currType = ParType::Allocated;
				allocPar = p;
			}
			else
			{
				Partition* par = new Partition(m_ParSerial++, job->requeireSize, p->initAddress, ParType::Allocated);
				m_ParList.push_back(par);
				allocPar = par;
				p->initAddress += job->requeireSize;
			}
			break;
		}
	}

	m_ParList.sort([](Partition* par1, Partition* par2)->bool {return  par1->initAddress < par2->initAddress; });
	return allocPar;
}

void OperatorSystem::RecycleMem(Job* job)
{
	for (auto& p : m_Jcbs)
	{
		if (p->pJob == job)
		{
			p->pPar->currType = ParType::Undistributed;
			break;
		}
	}
	//TODO���ϲ����պ��δ����ķ���
	bool flag = true;
	while (flag)
	{
		for (auto par = m_ParList.begin(); par != m_ParList.end();)
		{
			auto temp = par++;
			if (par != m_ParList.end())
			{
				if ((*temp)->currType == ParType::Undistributed && (*par)->currType == ParType::Undistributed)
				{
					if ((*temp)->initAddress + (*temp)->size == (*par)->initAddress)
					{
						//�ϲ�
						(*temp)->size += (*par)->size;
						m_ParList.erase(par);
						flag = true;
						break;
					}
				}
			}
			flag = false;
		}

	}
}

bool OperatorSystem::IsEnd()
{
	if (m_AllJobs.empty() && m_Jobs.empty() && !m_FinJobs.empty())
		return true;
	return false;
}
