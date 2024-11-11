#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

class Logger {
private:
    std::mutex logMutex;
    std::ofstream logFile;

    std::string getCurrentTimestamp();

public:
    Logger(const std::string& filename = "server.log");
    void log(const std::string& message, const std::string& level = "INFO");
    ~Logger();
};

#endif
