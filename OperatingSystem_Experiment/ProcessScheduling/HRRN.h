#pragma once
#include "ProcessScheduling.h"
class HRRN :
    public ProcessScheduling
{
public:
    HRRN();
    virtual ~HRRN();
    virtual void Scheuduled();
    virtual void ShowTime();

    PCB* GetMaxRRPCB();
};

