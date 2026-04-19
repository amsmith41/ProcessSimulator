#include "../include/Simulation.h"
#include "../include/Process.h"
#include "../include/Ischeduler.h"

Simulation::Simulation(std::vector<Process*> processes, IScheduler* scheduler)
    : processes(processes), scheduler(scheduler), runningProcess(nullptr), currentTime(0)
{
}   


void Simulation::run()
{
    bool allProcessesCompleted = false; 
    while (!allProcessesCompleted) {
        
            // Get the newly arrived process and add it to the ready queue
            for (Process* process : processes)
            {
                if (process->getState() == ProcessState::New && process->getArrivalTime() <= currentTime)
                {
                    process->setState(ProcessState::Ready); // New -> Ready state
                    scheduler->addProcess(process);
                }
            }

            // When the runningProcess == nullptr, the CPU is idle 
            // So we need to get the next process to run from the scheduler
            if (runningProcess == nullptr && scheduler->hasReadyProcesses())
            {
                runningProcess = scheduler->getNextProcess(currentTime);
                if (runningProcess != nullptr) 
                {
                    runningProcess->setState(ProcessState::Running);
                }
            }

            // Increment waiting time for every ready process
            for (Process* process : processes)
            {
                if (process->getState() == ProcessState::Ready)
                {
                    process->incrementWaitingTime();
                }
            }
            

        
    }
}
