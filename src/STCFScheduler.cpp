#include "../include/STCFScheduler.h"
#include "../include/Process.h" 

void STCFScheduler::addProcess(Process* process)
{
    if (process == nullptr)
    {
        return;
    }
    readyQueue.push(process);

    if (currentProcess != nullptr && currentProcess->getRemainingBurstTime() > readyQueue.top()->getRemainingBurstTime())
    {
        readyQueue.push(currentProcess);
        currentProcess = nullptr;
    }
}
 
Process* STCFScheduler::getNextProcess(int currentTime)
{
    if (readyQueue.empty() && currentProcess == nullptr) {
        return nullptr;
    }
    if (currentProcess != nullptr && (
        readyQueue.empty() || currentProcess->getRemainingBurstTime() <= readyQueue.top()->getRemainingBurstTime()
    ))
    {
        return currentProcess;
    }
    Process* nextProcess = readyQueue.top();
    readyQueue.pop();
    currentProcess = nextProcess;
    return currentProcess;
}
 
void STCFScheduler::onTick(int currentTime, Process* runningProcess)
{
    if (runningProcess == nullptr){
        currentProcess = nullptr;
    }
}
 
void STCFScheduler::onProcessBlocked(Process* process)
{
    // no process is running until cpu gets the next one
    currentProcess = nullptr;
}
 
void STCFScheduler::onProcessUnblocked(Process* process)
{
    addProcess(process);
}
 
void STCFScheduler::onProcessTerminated(Process* process)
{
}
 
bool STCFScheduler::hasReadyProcesses() const
{
    return !readyQueue.empty();
}
