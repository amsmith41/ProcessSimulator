#include "../include/Logger.h"
#include <iostream>
#include <string>

// Helper function to convert enum EventType to string
static std::string eventTypeToString(EventType eventType)
{
    switch (eventType)
    {
        case EventType::Arrival: return "Arrival";
        case EventType::Start: return "Start";
        case EventType::Resume: return "Resume";
        case EventType::Block: return "Block";
        case EventType::Unblock: return "Unblock";
        case EventType::Terminate: return "Terminate";
    }
}

// Constructor to initialize logger and open file stream
Logger::Logger(const std::string& filename)
{
    outFile.open(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening log file: " << filename << std::endl;
    }
}

// Destructor to close file stream if open
Logger::~Logger()
{
    if (outFile.is_open())
    {
        outFile.close();
    }
}

// Log an event with time, ProcessId, and the type of event
void Logger::logEvent(int time, int processId, EventType eventType)
{
    LogEntry entry{time, processId, eventType};
    logEntries.push_back(entry);

    if (outFile.is_open())
    {
        outFile << "Time" << time << ", Process " << processId << ", Event: " << eventTypeToString(eventType)
                << '\n';
    }
}

// Get log entries
const std::vector<LogEntry>& Logger::getLogEntries() const
{
    return logEntries;
}

// Print log entries
void Logger::print() const
{
    for (const auto& entry : logEntries)
    {
        std::cout << "Time " << entry.time << ", Process " << entry.processId << ", Event: " << eventTypeToString(entry.eventType) 
                  << '\n';
    }
}