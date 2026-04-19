#pragma once

#include <vector>

class Process;
class IScheduler;

class Simulation
{
    private:
        std::vector<Process*> processes; // List of all processes in simulation
        IScheduler* scheduler; // Scheduler to manage process execution
        Process* runningProcess; // Currently running process
        int currentTime; // Current time in the simulation

    public:
        void run(); // Run the simulation
        Simulation(std::vector<Process*> processes, IScheduler* scheduler); // Constructor that initializes a simulation with processes and scheduler policy(s)
    
};