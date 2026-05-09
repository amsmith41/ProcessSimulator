#pragma once

#include "Ischeduler.h"
#include "Process.h"
#include <queue>


class SJNScheduler : public IScheduler
{
    private:
    struct CompareBurstTime{
        bool operator()(const Process* p1, const Process* p2) {
            return p1->getRemainingBurstTime() > p2->getRemainingBurstTime();
        }
    };

    std::priority_queue<Process*, std::vector<Process*>, CompareBurstTime> readyQueue; // Queue to hold ready processes

    public:
        void addProcess(Process* process) override;
        Process* getNextProcess(int currentTime) override;
        void onTick(int currentTime, Process* runningProcess) override;
        void onProcessBlocked(Process* process) override;
        void onProcessUnblocked(Process* process) override; 
        void onProcessTerminated(Process* process) override;
        bool hasReadyProcesses() const override;
        //~SJNScheduler() = default;
};

