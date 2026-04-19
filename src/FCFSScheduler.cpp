#include "../include/FCFSScheduler.h"
#include "../include/Process.h" 

void FCFSScheduler::addProcess(Process* process)
{
    if (process != nullptr) {
    readyQueue.push(process);
    }
}

Process* FCFSScheduler::getNextProcess(int currentTime)
{
    if (readyQueue.empty()) {
        return nullptr;
    }
    Process* nextProcess = readyQueue.front();
    readyQueue.pop();
    return nextProcess;
}

void FCFSScheduler::onTick(int currentTime, Process* runningProcess)
{
    // FCFS does not employ the use of time slices, so there is no need for tick logic
}

void FCFSScheduler::onProcessBlocked(Process* process)
{
    // FCFS operates based on the ready queue, no need to handle blocked processes here
}

void FCFSScheduler::onProcessUnblocked(Process* process)
{
    addProcess(process);
}

void FCFSScheduler::onProcessTerminated(Process* process)
{
    // FCFS operates based on the ready queue, no need to handle terminated processes here
}

bool FCFSScheduler::hasReadyProcesses() const
{
    return !readyQueue.empty();
}