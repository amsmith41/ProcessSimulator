#include "../include/Logger.h"
#include <iostream>
#include <string>

Logger::Logger(const std::string& filename)
{
    outFile.open(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening log file: " << filename << std::endl;
    }
}

Logger::~Logger()
{
    if (outFile.is_open())
    {
        outFile.close();
    }
}

void Logger::logEvent(int time, int processId, EventType eventType)
{
    LogEntry entry{time, processId, eventType};
    logEntries.push_back(entry);

    if (outFile.is_open())
    {
        outFile << "Time" << time << ", Process " << processId << ", Event: "
                << '\n';

    }
}

const std::vector<LogEntry>& Logger::getLogEntries() const
{
    return logEntries;
}

void Logger::print() const
{

}