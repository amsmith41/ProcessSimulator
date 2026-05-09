#pragma once

#include "Ischeduler.h"
#include <queue>

class Process;

// First Come First Serve Scheduler
class RRScheduler : public IScheduler
{
    private:
        std::queue<Process*> readyQueue; // Queue to hold ready processes
        int timeQuantum = 5;
        int postQuantumTicks = 0; // The number of ticks since our last time slice.


    public:
        RRScheduler(int timeQuantum);
        void addProcess(Process* process) override;
        Process* getNextProcess(int currentTime) override;
        void onTick(int currentTime, Process* runningProcess) override;
        void onProcessBlocked(Process* process) override;
        void onProcessUnblocked(Process* process) override; 
        void onProcessTerminated(Process* process) override;
        bool hasReadyProcesses() const override;
};