#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logger {

    // Log a message to the log file and optionally print it to console
    void log(const std::string& message, bool printToConsole = true);

    // Returns the current log file path
    std::string getLogFilePath();

}

#endif
