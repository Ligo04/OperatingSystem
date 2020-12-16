#pragma once
#include "ProcessScheduling.h"
class RR :
    public ProcessScheduling
{
public:
    RR();
    virtual ~RR();
    virtual void Scheuduled();

    PCB* GetRentPCB();
protected:
    size_t currIndex;
};

