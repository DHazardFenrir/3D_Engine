#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>


enum LogLevel { LOGMessage, INFO, WARNING, LOGERROR, CRITICAL };

class Logger {
public:
    Logger() {}

    void Log(LogLevel level, const std::string& message);
    const std::vector<std::string>& GetLogs() const { return logMessages; }
    void LogConsole();
    void ClearLogs();
    ~Logger() {}

private:
    std::string levelToString(LogLevel level);
    std::vector<std::string> logMessages; 
    const size_t MAX_LOG_COUNT = 1000;
};



#endif // LOGGER_H
