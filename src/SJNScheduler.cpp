#include "../include/SJNScheduler.h"
#include "../include/Process.h" 
#include <iostream>

void SJNScheduler::addProcess(Process* process)
{
    if (process != nullptr){
        readyQueue.push(process);
    }
}
 
Process* SJNScheduler::getNextProcess(int currentTime)
{
    if (currentProcess != nullptr) return currentProcess;
    if (readyQueue.empty()) {
        return nullptr;
    }

    currentProcess = readyQueue.top();
    readyQueue.pop();
    return currentProcess;
}
 
void SJNScheduler::onTick(int currentTime, Process* runningProcess)
{
    if(runningProcess == nullptr)
        currentProcess = nullptr;
}
 
void SJNScheduler::onProcessBlocked(Process* process)
{
    if(currentProcess == process)
        currentProcess = nullptr;
}
 
void SJNScheduler::onProcessUnblocked(Process* process)
{
    addProcess(process);
}
 
void SJNScheduler::onProcessTerminated(Process* process)
{
    if(currentProcess == process)
        currentProcess = nullptr;
}
 
bool SJNScheduler::hasReadyProcesses() const
{
    return !readyQueue.empty();
}
