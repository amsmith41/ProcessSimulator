# 360CourseProject - Process Simulator

Project Overview and Goals
Create simulated processes with states (ready, running, blocked); multiple scheduling algorithms (FCFS, SJN, RR, STCF); virtual address translation simulation context-switch logging 

Themes:
  Process Control
  Process Scheduling
  Computer Memory Systems
  Control Flow & Linking Concepts

Design Decisions & Trade-offs:

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

  


