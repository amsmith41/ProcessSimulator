#include "../include/Process.h" 

Process::Process(int pid, int arrivalTime, const std::vector<BurstStep>& burstTimes)
    : pid(pid), arrivalTime(arrivalTime), burstTimes(burstTimes), currentBurstIndex(0), remainingBurstTime(0),
      totalRemainingCPUTime(0), waitingTime(0), turnaroundTime(0), completionTime(0), state(ProcessState::New)
{
   // Calculate total remaining CPU time based on the burst times
   if (!this->burstTimes.empty()){
    remainingBurstTime = this->burstTimes[0].duration; // Initialize remaining burst time to the first burst
   }

   for (const BurstStep& burst : burstTimes){
       if (burst.isCPU) {
           totalRemainingCPUTime += burst.duration;
       }
   }
}

int Process::getPid() const
{
    return pid;
}

int Process::getArrivalTime() const
{
    return arrivalTime;
}

ProcessState Process::getState() const
{
    return state;
}

void Process::setState(ProcessState newState)
{
    state = newState;
}

int Process::getRemainingBurstTime() const
{
    return remainingBurstTime;
}

bool Process::hasMoreBursts() const
{
    return !burstTimes.empty() && currentBurstIndex < burstTimes.size() - 1; // Check if there are more bursts after the current one
}

bool Process::isCPU() const
{
    if (burstTimes.empty() || currentBurstIndex >= burstTimes.size()) {
        return false; // No bursts or out of bounds, treat the burst as I/O instead of CPU
    }
    return burstTimes[currentBurstIndex].isCPU;
}

bool Process::isIO() const
{
    if (burstTimes.empty() || currentBurstIndex >= burstTimes.size()) {
        return false; // No bursts or out of bounds, treat the burst as CPU instead of I/O
    }
    return !burstTimes[currentBurstIndex].isCPU;
}

int Process::getTotalRemainingCPUTime() const
{
    return totalRemainingCPUTime;
}

int Process::getWaitingTime() const
{
    return waitingTime;
}

int Process::getTurnaroundTime() const
{
    return turnaroundTime;
}

int Process::getCompletionTime() const
{
    return completionTime;
}

void Process::decrementCurrentBurst()
{
    if (remainingBurstTime > 0)
    {
        remainingBurstTime--;
    }

    if (isCPU() && totalRemainingCPUTime > 0)
    {
        totalRemainingCPUTime--;
    }
}

bool Process::advanceToNextBurst()
{
    if (!hasMoreBursts())
    {
        return false; // No more bursts to advance to
    }

    currentBurstIndex++;
    remainingBurstTime = burstTimes[currentBurstIndex].duration; // Reset remaining burst time to the next burst's duration
    return true;
}

bool Process::isCompleted() const
{
    if (burstTimes.empty()) {
        return true; // Process is completed if there are no bursts
    }
    return currentBurstIndex == burstTimes.size() - 1 && remainingBurstTime == 0;
}

void Process::incrementWaitingTime()
{
    waitingTime++;
}

void Process::setCompletionTime(int time)
{
    completionTime = time;
}

void Process::calculateTurnaroundTime()
{
    turnaroundTime = completionTime - arrivalTime;
}



