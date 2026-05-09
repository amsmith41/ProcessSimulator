#include "../include/RRScheduler.h"
#include "../include/Process.h"

RRScheduler::RRScheduler(int timeQuantum) : timeQuantum(timeQuantum) {}

void RRScheduler::addProcess(Process *process)
{
  if (process != nullptr)
  {
    readyQueue.push(process);
  }
}

Process *RRScheduler::getNextProcess(int currentTime)
{
  if (readyQueue.empty())
  {
    return nullptr;
  }
  Process *nextProcess = readyQueue.front();
  return nextProcess;
}

void RRScheduler::onTick(int currentTime, Process *runningProcess)
{
  this->postQuantumTicks++;
  if (this->postQuantumTicks % this->timeQuantum == 0)
  { // Completed time slice
    this->postQuantumTicks = 0;
    if(!readyQueue.empty()) {
      // Move the current process to the back of the queue
      readyQueue.push(readyQueue.front());
      readyQueue.pop();
    }
  }
}

void RRScheduler::onProcessBlocked(Process *process)
{
  if (process == readyQueue.front())
  { // We need to remove the process from the queue so that another process can run
    //  (and eventually unblock this process)
    this->postQuantumTicks = 0;
    readyQueue.pop();
  }
}

void RRScheduler::onProcessUnblocked(Process *process)
{
  addProcess(process);
}

void RRScheduler::onProcessTerminated(Process *process)
{
  if (process == readyQueue.front())
  { // We need to remove the terminated process from the queue
    this->postQuantumTicks = 0;
    readyQueue.pop();
  }
}

bool RRScheduler::hasReadyProcesses() const
{
  return !readyQueue.empty();
}