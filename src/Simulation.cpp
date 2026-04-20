#include "../include/Simulation.h"
#include "../include/Process.h"
#include "../include/Ischeduler.h"
#include "../include/Logger.h"
#include <unordered_set> // There is current need in tracking which processes have already been placed in the CPU,
                         // This is a temporary stopgap to ensure that the logger is correctly logging the resume and start events

Simulation::Simulation(std::vector<Process*> processes, IScheduler* scheduler, Logger* logger)
    : processes(processes), scheduler(scheduler), runningProcess(nullptr), logger(logger), currentTime(0)
{
}   


void Simulation::run()
{
    bool allProcessesCompleted = false; 
    std::unordered_set<int> startedProcesses; // Set at the time a process starts running for the first time, used for logging

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

            // Update the state of blocked processes and check if they can become unblocked
            for (Process* process : processes)
            {
                if (process->getState() == ProcessState::Blocked)
                {
                    process->decrementCurrentBurst(); // Simulate one tick of the I/O burst for the blocked process

                    // Check if the blocked process can become unblocked
                    if (process->getRemainingBurstTime() == 0)
                    {
                        if (process->hasMoreBursts())
                        {
                            process->advanceToNextBurst();
                            process->setState(ProcessState::Ready);
                            scheduler->onProcessUnblocked(process);
                        }
                        else
                        {
                            process->setState(ProcessState::Terminated);
                            process->setCompletionTime(currentTime + 1);
                            process->calculateTurnaroundTime();
                            scheduler->onProcessTerminated(process);
                        }
                    }
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

                        if (runningProcess->isIO())
                        {
                            runningProcess->setState(ProcessState::Blocked);
                            scheduler->onProcessBlocked(runningProcess);
                        }
                        else // Is CPU burst, so we can add it back to the ready queue
                        {
                            runningProcess->setState(ProcessState::Ready);
                            scheduler->addProcess(runningProcess);
                        }
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

            // Increment waiting time for every ready process
            for (Process* process : processes)
            {
                if (process->getState() == ProcessState::Ready)
                {
                    process->incrementWaitingTime();
                }
            }

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
