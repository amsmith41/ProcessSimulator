#pragma once

#include <vector>

class Process;
class IScheduler;
class Logger;

class Simulation
{
    private:
        std::vector<Process*> processes; // List of all processes in simulation
        IScheduler* scheduler; // Scheduler to manage process execution
        Process* runningProcess; // Currently running process
        Logger* logger; // Logger to record events during the simulation
        int currentTime; // Current time in the simulation

    public:
        void run(); // Run the simulation
        Simulation(std::vector<Process*> processes, IScheduler* scheduler, Logger* logger); // Constructor that initializes a simulation with processes, scheduler policy(s), and logger

    };