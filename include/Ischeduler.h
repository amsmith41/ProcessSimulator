#pragma once

class Process;


// Interface for all scheduling algorithms
// Scheduler should not run the simulation, the simulation will be handled by the simulation.cpp file, 
// the scheduler will just provide the next process to run based on the scheduling algorithm

class IScheduler
{
    public:
        virtual ~IScheduler() = default;

        virtual void addProcess(Process* process) = 0; // Add to ready if and only if a new process arives, or a blocked process unblocks
        virtual Process* getNextProcess(int currentTime) = 0; // Get next process to run, return nullptr is no process is ready to run
        virtual void onTick(int currentTime, Process* runningProcess) = 0; // Call per simulation tick, useful for RRobin when tracking time
        virtual void onProcessBlocked(Process* process) = 0; // Call when process becomes blocked and cannot run until it becomes unblocked
        virtual void onProcessUnblocked(Process* process) = 0; // Call when process becomes unblocked and ready to run
        virtual void onProcessTerminated(Process* process) = 0; // Call when process terminates
        virtual bool hasReadyProcesses() const = 0; // Return true if < 1 processes are ready to run
};
