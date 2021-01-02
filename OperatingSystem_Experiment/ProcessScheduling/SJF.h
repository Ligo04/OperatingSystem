#pragma once
#include "ProcessScheduling.h"


class SJF :
    public ProcessScheduling
{
public:
    SJF();
    virtual ~SJF();
    virtual void Scheuduled();
    virtual void ShowTime();
    //void Show();

    PCB* GetMinNeedTime();
};

