#pragma once

#include "Ischeduler.h"
#include <queue>

class Process;

// First Come First Serve Scheduler
class FCFSScheduler : public IScheduler
{
    private:
        std::queue<Process*> readyQueue; // Queue to hold ready processes

    public:
        void addProcess(Process* process) override;
        Process* getNextProcess(int currentTime) override;
        void onTick(int currentTime, Process* runningProcess) override;
        void onProcessBlocked(Process* process) override;
        void onProcessUnblocked(Process* process) override; 
        void onProcessTerminated(Process* process) override;
        bool hasReadyProcesses() const override;
};