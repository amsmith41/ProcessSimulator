#pragma once


// Types of events that will occur during the simulation
enum class EventType
{
    Arrival, // Process arrives in queue
    Start, // Process starts running for the first time on CPU
    Resume, // Process resumes running on CPU after being unblocked
    Block, // Process is blocked for I/O
    Unblock, // Process finishes I/O and is unblocked
    Terminate // Process finished all its bursts and terminates
};