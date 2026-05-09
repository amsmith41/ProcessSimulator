#include "../include/SJNScheduler.h"
#include "../include/Process.h" 

void SJNScheduler::addProcess(Process* process)
{
    if (process != nullptr){
        readyQueue.push(process);
    }
}
 
Process* SJNScheduler::getNextProcess(int currentTime)
{
    if (readyQueue.empty()) {
        return nullptr;
    }
    Process* nextProcess = readyQueue.top();
    readyQueue.pop();
    return nextProcess;
}
 
void SJNScheduler::onTick(int currentTime, Process* runningProcess)
{

}
 
void SJNScheduler::onProcessBlocked(Process* process)
{
}
 
void SJNScheduler::onProcessUnblocked(Process* process)
{
    addProcess(process);
}
 
void SJNScheduler::onProcessTerminated(Process* process)
{
}
 
bool SJNScheduler::hasReadyProcesses() const
{
    return !readyQueue.empty();
}
