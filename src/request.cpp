#include "request.h"
#include "logger.h"
#include "response.h"
#include "server_stats.h"
#include "utils.h"
#include <unistd.h>
#include <cstring>

extern ServerStats serverStats;
const int BUFFER_SIZE = 30000;

void handleRequest(int socket) {
    auto start = std::chrono::high_resolution_clock::now();

    char buffer[BUFFER_SIZE] = {0};
    read(socket, buffer, BUFFER_SIZE);

    std::string request(buffer);

    size_t method_end = request.find(" ");
    size_t path_end = request.find(" ", method_end + 1);
    std::string path = request.substr(method_end + 1, path_end - method_end - 1);

    Logger logger;
    logger.log("Request received for path: " + path, "INFO");

    std::string file_path = getFilePath(path);

    if (file_path.empty()) {
        logger.log("File not found for path: " + path, "ERROR");
    } else {
        logger.log("Serving file: " + file_path, "INFO");
    }

    std::string response;
    int statusCode = 200;

    if (path == "/stats") {
            response = serverStats.getStatsHtml();
            statusCode = 200;
        } else {
            response = createResponse(file_path);
            if (response.find("404 Not Found") != std::string::npos) {
                statusCode = 404;
            }
        }

    logger.log("Sending response: " + response.substr(0, 50) + "...", "INFO");

    write(socket, response.c_str(), response.length());
    close(socket);

    auto end = std::chrono::high_resolution_clock::now();
    double responseTime = std::chrono::duration<double, std::milli>(end - start).count();

    serverStats.updateStats(path, statusCode, responseTime);
    logger.log("Response time: " + std::to_string(responseTime) + " ms", "DEBUG");
}
