#include <iostream>
#include <vector>
#include "../../include/Process.h"
#include "../../include/FCFSScheduler.h"
#include "../../include/Simulation.h"
#include "../../include/Logger.h"

void testSimulationBehavior()
{

    const int numPages = 8;

    Process p1(1, 0, std::vector<BurstStep>
    {
        {true, 3},   // CPU
        {false, 2},  // I/O
        {true, 1}    // CPU
    }, numPages);

    Process p2(2, 1, std::vector<BurstStep>
    {
        {true, 2}
    }, numPages);

    Process p3(3, 2, std::vector<BurstStep>
    {
        {true, 1}
    }, numPages);

    std::vector<Process*> processes = {&p1, &p2, &p3};

    FCFSScheduler scheduler;
    Logger logger("simulation.txt");
    
    Simulation simulation(processes, &scheduler, &logger);
    simulation.run();

    std::cout << "Simulation complete\n\n";

    std::cout << "P1\n";
    std::cout << "  Waiting Time: " << p1.getWaitingTime() << '\n';
    std::cout << "  Turnaround Time: " << p1.getTurnaroundTime() << '\n';
    std::cout << "  Completion Time: " << p1.getCompletionTime() << '\n';
    std::cout << "  Final State: "
              << (p1.getState() == ProcessState::Terminated ? "Terminated" : "Not Terminated")
              << "\n\n";

    std::cout << "P2\n";
    std::cout << "  Waiting Time: " << p2.getWaitingTime() << '\n';
    std::cout << "  Turnaround Time: " << p2.getTurnaroundTime() << '\n';
    std::cout << "  Completion Time: " << p2.getCompletionTime() << '\n';
    std::cout << "  Final State: "
              << (p2.getState() == ProcessState::Terminated ? "Terminated" : "Not Terminated")
              << "\n\n";

    std::cout << "P3\n";
    std::cout << "  Waiting Time: " << p3.getWaitingTime() << '\n';
    std::cout << "  Turnaround Time: " << p3.getTurnaroundTime() << '\n';
    std::cout << "  Completion Time: " << p3.getCompletionTime() << '\n';
    std::cout << "  Final State: "
              << (p3.getState() == ProcessState::Terminated ? "Terminated" : "Not Terminated")
              << "\n";
}

// Current testing behavior only checks for alternation of CPU and I/O bursts,
// There is need to test for CPU->CPU->CPU... I/O->I/O->I/O... and other burst patterns to ensure program robustness
int main()
{
    testSimulationBehavior();
    return 0;
}