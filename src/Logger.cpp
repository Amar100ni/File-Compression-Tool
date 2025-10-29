#include "Logger.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace Logger {

    static std::string logFilePath = "logs/activity_log.txt";

    void log(const std::string& message, bool printToConsole) {
        std::filesystem::create_directories("logs");

        std::ofstream logFile(logFilePath, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "[Logger Error] Unable to open log file.\n";
            return;
        }

        // Get timestamp
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timestamp = std::ctime(&now);
        timestamp.pop_back(); // remove newline

        std::string entry = "[" + timestamp + "] " + message + "\n";

        logFile << entry;
        logFile.close();

        if (printToConsole)
            std::cout << entry;
    }

    std::string getLogFilePath() {
        return logFilePath;
    }

}
