#include "Logger.h"
#include "imgui.h"


void Logger::Log(LogLevel level, const std::string& message) {
    time_t now = time(0);
    tm* timeInfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeInfo);

    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << levelToString(level) << " :: " << message;

    std::string logMessage = logEntry.str();
    logMessages.push_back(logMessage); 
    std::cout << logMessage << std::endl; 
}

void Logger::LogConsole()
{
    if (ImGui::Begin("Console")) { 
        const std::vector<std::string>& logs = GetLogs();

        for (const std::string& log : logs) {
            ImGui::TextUnformatted(log.c_str()); 
        }

        
        if (ImGui::Button("Clear Logs")) {
            const_cast<std::vector<std::string>&>(logs).clear(); 
        }
    }
    ImGui::End();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case LOGMessage: return "LOG";
    case INFO: return "INFO";
    case WARNING: return "WARNING";
    case LOGERROR: return "ERROR";
    case CRITICAL: return "CRITICAL";
    default: return "UNKNOWN";
    }
}
