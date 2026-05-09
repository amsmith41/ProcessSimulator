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
    return nextProcess;
}

void FCFSScheduler::onTick(int currentTime, Process* runningProcess)
{
    // FCFS does not employ the use of time slices, so there is no need for tick logic
}

void FCFSScheduler::onProcessBlocked(Process* process)
{
    if(process == readyQueue.front()) { // We need to remove the process from the queue so that another process can run
                                        //  (and eventually unblock this process)
        readyQueue.pop();
    }
}

void FCFSScheduler::onProcessUnblocked(Process* process)
{
    addProcess(process);
}

void FCFSScheduler::onProcessTerminated(Process* process)
{
    if(process == readyQueue.front()) { // We need to remove the terminated process from the queue
        readyQueue.pop();
    }
}

bool FCFSScheduler::hasReadyProcesses() const
{
    return !readyQueue.empty();
}