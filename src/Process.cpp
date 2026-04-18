#include "../include/Process.h" 

Process::Process(int pid, int arrivalTime, const std::vector<BurstStep>& burstTimes)
    : pid(pid), arrivalTime(arrivalTime), burstTimes(burstTimes), currentBurstIndex(0), remainingBurstTime(0),
      totalRemainingCPUTime(0), waitingTime(0), turnaroundTime(0), completionTime(0), state(ProcessState::New)
{
   // Calculate total remaining CPU time based on the burst times
   if (!this->burstTimes.empty()){
    remainingBurstTime = burstTimes[0].duration; // Initialize remaining burst time to the first burst
   }

   for (const BurstStep& burst : burstTimes){
       if (burst.isCPU) {
           totalRemainingCPUTime += burst.duration;
       }
   }
}