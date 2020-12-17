#pragma once
#include "ProcessScheduling.h"
class HRRN :
    public ProcessScheduling
{
public:
    HRRN();
    virtual ~HRRN();
    virtual void Scheuduled();


    PCB* GetMaxRRPCB();
};

