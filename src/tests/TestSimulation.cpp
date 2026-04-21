#include <iostream>
#include <vector>
#include "../../include/Process.h"
#include "../../include/FCFSScheduler.h"
#include "../../include/Simulation.h"
#include "../../include/Logger.h"
#include "../../include/MemoryManager.h"

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

void testMemoryTranslation()
{
    const int numPages = 8;
    const int pageSize = 256;
    const int numFrames = 16;

    Process p4(4, 0, std::vector<BurstStep>
    {
        {true, 1}
    }, numPages);

    MemoryManager memoryManager(pageSize, numFrames);

    // Map virtual page 2 to physical frame 5
    p4.getPageTable().mapPage(2, 5);

    // Test mapped address: 529 = page 2, offset 17
    AddressTranslation mappedResult = memoryManager.translateAddress(&p4, 529);

    std::cout << "Memory Translation Test\n";
    std::cout << "Mapped address test (virtual address 529)\n";
    std::cout << "  Valid: " << (mappedResult.valid ? "true" : "false") << '\n';
    std::cout << "  Virtual Page Number: " << mappedResult.virtualPageNumber << '\n';
    std::cout << "  Offset: " << mappedResult.offset << '\n';
    std::cout << "  Frame Number: " << mappedResult.frameNumber << '\n';
    std::cout << "  Physical Address: " << mappedResult.physicalAddress << "\n\n";

    // Test unmapped address: page 3 is not mapped
    AddressTranslation unmappedResult = memoryManager.translateAddress(&p4, 800);

    std::cout << "Unmapped address test (virtual address 800)\n";
    std::cout << "  Valid: " << (unmappedResult.valid ? "true" : "false") << '\n';
    std::cout << "  Virtual Page Number: " << unmappedResult.virtualPageNumber << '\n';
    std::cout << "  Offset: " << unmappedResult.offset << '\n';
    std::cout << "  Frame Number: " << unmappedResult.frameNumber << '\n';
    std::cout << "  Physical Address: " << unmappedResult.physicalAddress << "\n\n";

    // Test invalid negative address
    AddressTranslation invalidResult = memoryManager.translateAddress(&p4, -1);

    std::cout << "Invalid address test (virtual address -1)\n";
    std::cout << "  Valid: " << (invalidResult.valid ? "true" : "false") << '\n';
    std::cout << "  Virtual Page Number: " << invalidResult.virtualPageNumber << '\n';
    std::cout << "  Offset: " << invalidResult.offset << '\n';
    std::cout << "  Frame Number: " << invalidResult.frameNumber << '\n';
    std::cout << "  Physical Address: " << invalidResult.physicalAddress << "\n\n";
}

// Current testing behavior only checks for alternation of CPU and I/O bursts,
// There is need to test for CPU->CPU->CPU... I/O->I/O->I/O... and other burst patterns to ensure program robustness
int main()
{
    testSimulationBehavior();
    std::cout << '\n';
    testMemoryTranslation();
    return 0;
}