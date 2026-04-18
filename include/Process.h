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

struct BurstStep
{
    // CPU/IO bursts are fundamental in driving processs state changes.
    // Without these, states are just labels with no behavior
    bool isCPU; // True if the type of burst is a CPU burst, false if an I/O burst
    int duration; // Duration of the burst
};


class Process
{
    private:
        int pid; // Process ID
        ProcessState state; // Current state of the process
        int arrivalTime; // Time when the process arrived in the system

        std::vector<BurstStep> burstTimes; // Sequence of CPU and I/O bursts for a process
        int currentBurstIndex; // Index of the current CPU burst being executed
        int remainingBurstTime; // Remaining time for the current CPU burst

        int totalRemainingCPUTime; // Total remaining CPU time for the process (useful for SJN and STCF)

        int waitingTime; // Total waiting time for the process
        int turnaroundTime; // Total turnaround time for the process
        int completionTime; // Time when the process completed execution

    public:
        /*
            Construction of a process with a process ID, arrival time, and CPU burst times
        */
        Process(int pid, int arrivalTime, const std::vector<BurstStep>& burstTimes);

        int getPid() const; // Get the process ID
        int getArrivalTime() const; // Get the arrival time of the process
        ProcessState getState() const; // Get the current state of the process
        void setState(ProcessState newState); // Set the state of the process

        int getRemainingBurstTime() const; // Get the remaining time for the current CPU burst
        bool hasMoreBursts() const; // Check if the process has more bursts to execute
        bool isCPU() const; // Check if the current burst is a CPU burst
        bool isIO() const; // Check if the current burst is an I/O burst

        int getTotalRemainingCPUTime() const; // Get the total remaining CPU time for the process
        int getWaitingTime() const; // Get the total waiting time for the process
        int getTurnaroundTime() const; // Get the total turnaround time for the process
        int getCompletionTime() const; // Get the completion time of the process

        void decrementCurrentBurst(); // Decrement time of current CPU burst
        bool advanceToNextBurst(); // Move to the next burst in the sequence, returns false if no more bursts are remaining
        bool isCompleted() const; // Check if the process has completed all its bursts
        void incrementWaitingTime(); // Increment the waiting time for the process
        void setCompletionTime(int time); // Set the completion time for the process
        void calculateTurnaroundTime(); // Calculate the turnaround time for the process based on arrival and completion times
};