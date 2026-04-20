#pragma once

#include <vector>
#include <string>
#include <fstream>

// Types of events that will occur during the simulation
enum class EventType
{
    Arrival, // Process arrives in queue
    Start, // Process starts running for the first time on CPU
    Resume, // Process resumes running on CPU after being unblocked
    Block, // Process is blocked for I/O
    Unblock, // Process finishes I/O and is unblocked
    Terminate, // Process finished all its bursts and terminates
    ContextSwitch // Context switch occurs
};

struct LogEntry
{
    int time; // Simulation time when event occurs
    int processId; // ID of the process involved in the event
    EventType eventType; // Type of event that occurred
    int fromProcessId; // For context switch events, the process that is being switched out, -1 if none
    int toProcessId; // For context switch events, the process that is being switched in, -1 if none
    std::string contextReason; // For context switch events, the reason for the context switch

};

class Logger
{
    private:
        std::vector<LogEntry> logEntries; // Object to hold all log entries
        std::ofstream outFile; // Output file stream when logging to a file

    public:
        Logger(const std::string& filename); // Initialize logger and open file stream
        ~Logger(); // Close file stream if open

        void logEvent(int time, int processId, EventType eventType); // Log an event with time, ProcessID, and the type of event
        const std::vector<LogEntry>& getLogEntries() const; // Get log entires
        void print() const; // Print log entries
};