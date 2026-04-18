#pragma once

#include <vector>

/*
    Representation of the state of a process
    Ready is process is ready to run
    Running is process is currently running
    Blocked is process is waiting for an event to finish or a resource to free up
    Terminated is process has finished execution
*/
enum class ProcessState
{
    Ready,
    Running,
    Blocked,
    Terminated
};

class Process
{
    private:
        int pid; // Process ID
        ProcessState state; // Current state of the process
        int arrivalTime; // Time when the process arrived in the system        

        int totalRemainingCPUTime; // Total remaining CPU time for the process (useful for SJN and STCF)

        int waitingTime; // Total waiting time for the process
        int turnaroundTime; // Total turnaround time for the process
        int completionTime; // Time when the process completed execution

    public:
        /*
            Construction of a process with a process ID, arrival time, and CPU burst times
        */
        Process(int pid, int arrivalTime, const std::vector<int>& burstTimes);

        int getPid() const; // Get the process ID
        int getArrivalTime() const; // Get the arrival time of the process
        ProcessState getState() const; // Get the current state of the process
        void setState(ProcessState newState); // Set the state of the process

        int getTotalRemainingCPUTime() const; // Get the total remaining CPU time for the process
        int getWaitingTime() const; // Get the total waiting time for the process
        int getTurnaroundTime() const; // Get the total turnaround time for the process
        int getCompletionTime() const; // Get the completion time of the process

};