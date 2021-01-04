#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OS_UI.h"
#include "OperatorSystem.h"


class OS_UI : public QMainWindow
{
    Q_OBJECT

public:
    OS_UI(QWidget *parent = Q_NULLPTR);
    void Init();
    void Display();
    bool IsJobsEnd();
private slots:
    void StartSim();
    void Work();
    void SetDefaultJobs();
    void AddJobToOs();
    void BlockPCB();
private:
    Ui::OS_UIClass ui;
    std::vector<Job*>    m_PoolJobs;               //后备作业队列
    //bool                 m_IsPause = false;      //是否暂停
    int                  m_Time = 0;               //运行时间
    int                  m_TimeScalce = 200;       //时间间隔
    QTimer*              m_timer;
    OperatorSystem*      m_pOs;                    //操作系统
private:
    int             defaultNum = 10;
    int             num = 0;
    int             minSize = 10;
    int             maxSize = 100;
    int             minNeed = 10;
    int             maxNeed = 30;
    int             minArrive = 0;
    int             maxArrive = 40;
};
