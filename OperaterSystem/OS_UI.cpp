#include "OS_UI.h"
#include<qmessagebox.h>
#include<Windows.h>
#include<qtimer.h>
#if defined(_MSC_VER) && (_MSC_VER >= 1600)    
#pragma execution_character_set("utf-8")    
#endif

OS_UI::OS_UI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_PoolJobs = std::vector<Job*>();
    m_pOs = new OperatorSystem(1024, 2);
    m_timer = new QTimer(this);
    Init();
    Display();
}

void OS_UI::Init()
{
    QHeaderView* header1 = ui.PoolTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.PushJobTabelWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.RunJobTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.FinJobTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.MemTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.RunPCBTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.WaitPCBTableWidget->verticalHeader();
    header1->setHidden(true);
    header1 = ui.BlockPCBTabelWidget->verticalHeader();
    header1->setHidden(true);
    //禁止编辑
    ui.PoolTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.PushJobTabelWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.MemTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.RunPCBTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.WaitPCBTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.RunJobTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.FinJobTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui.BlockPCBTabelWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑



    connect(ui.DefaultPushButton, SIGNAL(clicked()), this, SLOT(SetDefaultJobs()));
    connect(ui.StartPushButton, SIGNAL(clicked()), this, SLOT(StartSim()));
    connect(ui.ADDJobPushButton, SIGNAL(clicked()), this, SLOT(AddJobToOs()));
    connect(ui.BlockPCBPushButton, SIGNAL(clicked()), this, SLOT(BlockPCB()));
    ui.BlockPCBPushButton->setEnabled(false);
}
void OS_UI::StartSim()
{
    ui.DefaultPushButton->setEnabled(false);
    ui.StartPushButton->setEnabled(false);
    ui.ADDJobPushButton->setEnabled(false);
    ui.BlockPCBPushButton->setEnabled(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Work()));
    m_timer->start(m_TimeScalce); //time specified in ms
}

void OS_UI::Work()
{
    if (!m_PoolJobs.empty())
    {
        if (m_PoolJobs.front()->arriveTime >= m_Time)
        {
            Job* job = m_PoolJobs.front();
            m_pOs->EnterJob(job);
            m_PoolJobs.erase(m_PoolJobs.begin());
        }
    }
    m_pOs->Scheduling();
    Display();
    if (IsJobsEnd() && m_pOs->IsEnd())
    {
        m_timer->stop();
        ui.DefaultPushButton->setEnabled(true);
        ui.StartPushButton->setEnabled(true);
        ui.ADDJobPushButton->setEnabled(true);
        ui.BlockPCBPushButton->setEnabled(false);
    }
    m_Time++;
}

void OS_UI::SetDefaultJobs()
{
    m_PoolJobs = std::vector<Job*>();
    num = 0;
    for (int i = 0; i < defaultNum; ++i)
    {
        std::string jobname = "作业" + std::to_string(num++);
        int size = random_int(minSize, maxSize);
        int need = random_int(minNeed, maxNeed);
        int arr = random_int(minArrive, maxArrive);
        Job* job = new Job(jobname, size, arr, need);
        m_PoolJobs.push_back(job);
    }
    std::sort(m_PoolJobs.begin(), m_PoolJobs.end(), [](Job* job1, Job* job2)->bool {return job1->arriveTime < job2->arriveTime; });
    Display();
}

void OS_UI::AddJobToOs()
{
    std::string jobname = ui.JobNameLineEdit->text().toStdString();
    int arrive = ui.JobArriveLineEdit->text().toInt();
    int need = ui.JobNeedLineEdit->text().toInt();
    int size = ui.JobSizeLineEdit->text().toInt();
    if (arrive <= 0 || need <= 0 || size <= 0)
    {
        QMessageBox::warning(this, "wraning", "参数错误（<=0）!!!请重新输入");
        return;
    }
    Job* job = new Job(jobname, size, arrive, need);
    m_PoolJobs.push_back(job);
    std::sort(m_PoolJobs.begin(), m_PoolJobs.end(), [](Job* job1, Job* job2)->bool {return job1->arriveTime < job2->arriveTime; });
    Display();
}


void OS_UI::Display()
{
    //后备作业队列
    ui.PoolTableWidget->setColumnCount(4);
    ui.PoolTableWidget->setRowCount(m_PoolJobs.size());
    for (size_t i = 0; i < m_PoolJobs.size(); ++i)
    {
        Job* job = m_PoolJobs[i];
        ui.PoolTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(job->jobName)));
        ui.PoolTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(job->arriveTime))));
        ui.PoolTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(job->needTime))));
        ui.PoolTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(job->requeireSize))));
    }

    //提交的作业
    ui.PushJobTabelWidget->setColumnCount(4);
    ui.PushJobTabelWidget->setRowCount(m_pOs->m_AllJobs.size());
    for (size_t i = 0; i < m_pOs->m_AllJobs.size(); ++i)
    {
        Job* job = m_pOs->m_AllJobs.front();
        m_pOs->m_AllJobs.pop();
        ui.PushJobTabelWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(job->jobName)));
        ui.PushJobTabelWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(job->arriveTime))));
        ui.PushJobTabelWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(job->needTime))));
        ui.PushJobTabelWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(job->requeireSize))));
        m_pOs->m_AllJobs.push(job);
    }

    //正在运行的作业
    ui.RunJobTableWidget->setColumnCount(4);
    ui.RunJobTableWidget->setRowCount(m_pOs->m_Jobs.size());
    for (size_t i = 0; i < m_pOs->m_Jobs.size(); ++i)
    {
        Job* job = m_pOs->m_Jobs[i];
        ui.RunJobTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(job->jobName)));
        ui.RunJobTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(job->arriveTime))));
        ui.RunJobTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(job->needTime))));
        ui.RunJobTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(job->requeireSize))));
    }

    //已经完成的作业
    ui.FinJobTableWidget->setColumnCount(4);
    ui.FinJobTableWidget->setRowCount(m_pOs->m_FinJobs.size());
    for (size_t i = 0; i < m_pOs->m_FinJobs.size(); ++i)
    {
        Job* job = m_pOs->m_FinJobs[i];
        ui.FinJobTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(job->jobName)));
        ui.FinJobTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(job->arriveTime))));
        ui.FinJobTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(job->needTime))));
        ui.FinJobTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(job->requeireSize))));
    }
    //内存分布情况
    ui.MemTableWidget->setColumnCount(4);
    ui.MemTableWidget->setRowCount(m_pOs->m_ParList.size());
    for (size_t i = 0; i < m_pOs->m_ParList.size(); ++i)
    {
        Partition* par = m_pOs->m_ParList.front();
        m_pOs->m_ParList.pop_front();
        ui.MemTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(par->parSerial))));
        ui.MemTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(par->initAddress)+"KB")));
        ui.MemTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(par->size)+"KB")));
        ui.MemTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(par->CurrTypeToStdString())));
        m_pOs->m_ParList.push_back(par);
    }
    //进程信息
    //正在运行的进程
    PCB* pcb = m_pOs->m_RR->currPCB;
    if (pcb != nullptr)
    {
        ui.RunPCBTableWidget->setColumnCount(3);
        ui.RunPCBTableWidget->setRowCount(1);
        ui.RunPCBTableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(pcb->name)));
        ui.RunPCBTableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->ranTime))));
        ui.RunPCBTableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->needTime))));
    }
    else
    {
        ui.RunPCBTableWidget->setColumnCount(0);
        ui.RunPCBTableWidget->setRowCount(0);
    }
    //正在等待的进程
    ui.WaitPCBTableWidget->setColumnCount(3);
    ui.WaitPCBTableWidget->setRowCount(m_pOs->m_RR->m_PCBQueue.size());
    for (size_t i = 0; i < m_pOs->m_RR->m_PCBQueue.size(); ++i)
    {
        pcb = m_pOs->m_RR->m_PCBQueue.front();
        m_pOs->m_RR->m_PCBQueue.pop();
        ui.WaitPCBTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(pcb->name)));
        ui.WaitPCBTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->ranTime))));
        ui.WaitPCBTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->needTime))));
        m_pOs->m_RR->m_PCBQueue.push(pcb);
    }
    //阻塞的进程
    ui.BlockPCBTabelWidget->setColumnCount(3);
    ui.BlockPCBTabelWidget->setRowCount(m_pOs->m_RR->m_PCBBlockQueue.size());
    for (size_t i = 0; i < m_pOs->m_RR->m_PCBBlockQueue.size(); ++i)
    {
        pcb = m_pOs->m_RR->m_PCBBlockQueue.front();
        m_pOs->m_RR->m_PCBBlockQueue.pop();
        ui.BlockPCBTabelWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(pcb->name)));
        ui.BlockPCBTabelWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->ranTime))));
        ui.BlockPCBTabelWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(pcb->needTime))));
        m_pOs->m_RR->m_PCBBlockQueue.push(pcb);
    }

    //居中
    for (int i = 0; i < ui.PushJobTabelWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.PushJobTabelWidget->columnCount(); ++j)
        {
            ui.PushJobTabelWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.PoolTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.PoolTableWidget->columnCount(); ++j)
        {
            ui.PoolTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.MemTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.MemTableWidget->columnCount(); ++j)
        {
            ui.MemTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }

    for (int i = 0; i < ui.RunPCBTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.RunPCBTableWidget->columnCount(); ++j)
        {
            ui.RunPCBTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.WaitPCBTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.WaitPCBTableWidget->columnCount(); ++j)
        {
            ui.WaitPCBTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.BlockPCBTabelWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.BlockPCBTabelWidget->columnCount(); ++j)
        {
            ui.BlockPCBTabelWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.RunJobTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.RunJobTableWidget->columnCount(); ++j)
        {
            ui.RunJobTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    for (int i = 0; i < ui.FinJobTableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui.FinJobTableWidget->columnCount(); ++j)
        {
            ui.FinJobTableWidget->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
}

bool OS_UI::IsJobsEnd()
{
    if (m_PoolJobs.empty())
        return true;
    return false;
}

void OS_UI::BlockPCB()
{
    m_pOs->m_RR->RandomBlockPCB();
}
