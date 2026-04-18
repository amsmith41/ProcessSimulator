#pragma once

/*
    Representation of the state of a process. 
    Ready is process is ready to run
    Running is process is currently running
    Blocked is process is waiting for an event to finish or a resource to free up
    Terminated is process has finished execution
*/
enum class ProcessState
{
    Ready,
    Running,
    Blocked,
    Terminated
};