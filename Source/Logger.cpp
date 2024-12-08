#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

enum LogLevel {LOG, INFO, WARNING, ERROR, CRITICAL};

class Logger {
public:
	Logger() 
	{}

	void Log(LogLevel level, const std::string& message) {
		time_t now = time(0);
		tm* timeInfo = localtime(&now);
		char timestamp[20];
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeInfo);
		std::ostringstream logEntry;

		logEntry << "[" << timestamp << "] " << levelToString(level) << " :: " << message << std::endl;

		std::cout << logEntry.str();


	}
	~Logger(){}

private:
	std::string levelToString(LogLevel level) {
		switch (level) {
		case LOG:
			return "LOG";
		case INFO:
			return "INFO";
		case WARNING:
			return "WARNING";
		case ERROR:
			return "ERROR";
		case CRITICAL:
			return "CRITICAL";
		default:
			return "UNKNOWN";
		}
	}
};