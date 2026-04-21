# 360CourseProject - Process Simulator

Project Overview and Goals
Create simulated processes with states (ready, running, blocked); multiple scheduling algorithms (FCFS, SJN, RR, STCF); virtual address translation simulation context-switch logging 

Themes:
  Process Control
    - Process States (New,Ready,Running,Blocked,Unblocked,Terminated)
    - In the Process class and manipulated by the Simulation
  Process Scheduling
    - Multiple scheduling policies of FCFS, RRobin, Shortest Job Next, Shortest time to completion first
  Computer Memory Systems
    - Page mapping
    - Memory Translation
  Control Flow & Linking Concepts
    - Control flow is expressed mostly in the Simulation engine of Simulation.cpp
      - With each tick of the runtime system, arrivals are introduced, progression of I/O is simulated, scheduling decisions based off stateness, the transition of said states, and the logging of events occuring
      - The state of a process determines what action to take

      main ---> simulation -> Ischeduler
                           -> Process
                           -> Memory Manager -> Page Table

      Abstraction with a scheduler interface
      Makefile to link compilation of multiple files
    

Design Decisions & Trade-offs:

Dependency direction when creating the foundation of the project...

Challenges Encountered and Lessons Learned:


Notes:

Suppose that page size is 256
A process as is defined in the test, is currently 8, this is the virtual pages
If a mapping of virtual page 2 to physical frame 5 occured; 2v-> 5p
The translation of such event would be 2 * 256 * 17 = 529
where 
page = 2 
offset = 17 (virtualAddres % pageSize)
frame = 5
physical address = 5 * 256 + 17 = 1297

How to Run:
make test
./test_sim

  after finished, make clean
  and you can examine the results in the simulation.txt file




