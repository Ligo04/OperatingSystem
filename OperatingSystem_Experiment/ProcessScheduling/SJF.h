#pragma once
#include "ProcessScheduling.h"


class SJF :
    public ProcessScheduling
{
public:
    SJF();
    virtual ~SJF();
    virtual void Scheuduled();
    //void Show();
    virtual bool IsEnd();

    PCB* GetMinNeedTime();
};

