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

    int lastExitedProcessId = -1; // Log context switch events, tracks last process that exited the CPU
    std::string contextSwitchReason; // Log context switch events, tracks the reason for the context switch

    while (!allProcessesCompleted) {
        // TICK

        // Handle moving existing processes through the pipeline
        for (Process* process : processes)
        {
            switch (process->getState()){
                case ProcessState::New: // Insert new processes into the scheduler
                    if(process->getArrivalTime() <= currentTime) {
                        process->setState(ProcessState::Ready); // New -> Ready state
                        scheduler->addProcess(process);

                        if (logger != nullptr)
                        {
                            logger->logEvent(currentTime, process->getPid(), EventType::Arrival);
                        }
                    }
                break;

                case ProcessState::Blocked:  // Update the state of blocked processes and check if they can become unblocked
                    process->decrementCurrentBurst(); // Simulate one tick of the I/O burst for the blocked process


                    // Check if the blocked process can become unblocked
                    if (process->getRemainingBurstTime() == 0)
                    {
                        if (process->hasMoreBursts())
                        {
                            process->advanceToNextBurst();
                            process->setState(ProcessState::Ready);
                            scheduler->onProcessUnblocked(process);

                            if (logger != nullptr)
                            {
                                logger->logEvent(currentTime + 1, process->getPid(), EventType::Unblock);
                            }
                        }
                        else
                        {
                            process->setState(ProcessState::Terminated);
                            process->setCompletionTime(currentTime + 1);
                            process->calculateTurnaroundTime();
                            scheduler->onProcessTerminated(process);

                            if (logger != nullptr)
                            {
                                logger->logEvent(currentTime + 1, process->getPid(), EventType::Terminate);
                            }
                        }
                    }
                break;
            }
        }

        // When the runningProcess == nullptr, the CPU is idle.
        // Get the burst that we are going to execute for one tick from the scheduler.
        runningProcess = scheduler->getNextProcess(currentTime);

        if (runningProcess != nullptr)
        {
            if (logger != nullptr)
            {
                if ( lastExitedProcessId == -1)
                {          
                    logger->logContextSwitch(currentTime, -1, runningProcess->getPid(), "CPU Idle -> Start Process");
                }
                else if (lastExitedProcessId != runningProcess->getPid())
                {
                                                                                                            // \/ This section is a bit rough, but we don't have another control flow for when processes have been swapped.
                    logger->logContextSwitch(currentTime, lastExitedProcessId, runningProcess->getPid(), (contextSwitchReason.empty()) ? "Scheduler has swapped processes":contextSwitchReason);
                }
            }

            runningProcess->setState(ProcessState::Running);
            lastExitedProcessId = runningProcess->getPid();

            if (logger != nullptr)
            {
                // Unordered set required at this point to determine if a process 
                // Is starting for the first time, or has already been started in the past and is now resuming
                // Resuming is helpful for future scheduling algorithms like RRobin
                if (startedProcesses.find(runningProcess->getPid()) == startedProcesses.end())
                {
                    logger->logEvent(currentTime, runningProcess->getPid(), EventType::Start);
                    startedProcesses.insert(runningProcess->getPid());
                }
                else
                {
                    logger->logEvent(currentTime, runningProcess->getPid(), EventType::Resume);
                }
                
            }

            // Reset context switch tracking variables
            contextSwitchReason.clear();
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

                        if (logger != nullptr)
                        {
                            logger->logEvent(currentTime + 1, runningProcess->getPid(), EventType::Block);
                        }

                        contextSwitchReason = "Process has been blocked";

                        runningProcess->setState(ProcessState::Blocked);
                        scheduler->onProcessBlocked(runningProcess);

                    }
                    else // Is CPU burst, so we can add it back to the ready queue
                    {
                        // This code doesn't seem to get called, either that or contextSwitchReason is being overwritten somewhere.
                        contextSwitchReason = "CPU burst completed";

                        runningProcess->setState(ProcessState::Ready);
                        // This line breaks Round Robin but also catches some edge cases in STCF, so we need to refactor RR
                        //scheduler->addProcess(runningProcess);
                    }
                }
                else
                {
                    if (logger != nullptr)
                    {
                        logger->logEvent(currentTime + 1, runningProcess->getPid(), EventType::Terminate);
                    }

                    contextSwitchReason = "Process has terminated";

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
