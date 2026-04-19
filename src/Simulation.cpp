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
            
            // Simulate one tick of the running process that is currently running
            if (runningProcess != nullptr)
            {
                runningProcess->decrementCurrentBurst();

                // If and when the process finishes bursting
                if (runningProcess->getRemainingBurstTime() == 0)
                {
                    if (runningProcess->hasMoreBursts())
                    {
                        runningProcess->advanceToNextBurst();
                        runningProcess->setState(ProcessState::Ready);
                        scheduler->addProcess(runningProcess);
                    }
                    else
                    {
                        runningProcess->setState(ProcessState::Terminated);
                        runningProcess->setCompletionTime(currentTime + 1);
                        runningProcess->calculateTurnaroundTime();
                        scheduler->onProcessTerminated(runningProcess);
                    }

                    runningProcess = nullptr; // CPU becomes idle after process finishes its burst
                }
            }

            scheduler->onTick(currentTime, runningProcess); // Update internal state of scheduler

            // Check if all processes have completed, if so we can end the simulation
            allProcessesCompleted = true; 
            for (Process* process : processes)
            {
                if (process->getState() != ProcessState::Terminated)
                {
                    allProcessesCompleted = false;
                    break;
                }
            }

            ++currentTime; // Increment the current time after each tick

    }
}
