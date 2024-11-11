#include "response.h"
#include "utils.h"
#include "logger.h"
#include <string>

std::string createResponse(const std::string &file_path) {
    Logger logger;

    logger.log("Attempting to read file: " + file_path, "INFO");

    std::string content = readFile(file_path);
    std::string response;

    if (!content.empty()) {
        std::string mime_type = getMimeType(file_path);
        logger.log("File found, serving: " + file_path + " with MIME type: " + mime_type, "INFO");
        logger.log("Content length: " + std::to_string(content.length()) + " bytes", "INFO");

        response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: " + mime_type + "\r\n";
        response += "Content-Length: " + std::to_string(content.length()) + "\r\n";
        response += "\r\n";
        response += content;
    } else {
        // 404 response
        logger.log("File not found, sending 404 response for: " + file_path, "ERROR");

        std::string not_found_content = readFile("public/404.html");
        if (not_found_content.empty()) {
            not_found_content = "<html><body><h1>404 - Page Not Found</h1></body></html>";
        }

        response = "HTTP/1.1 404 Not Found\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: " + std::to_string(not_found_content.length()) + "\r\n";
        response += "\r\n";
        response += not_found_content;
    }

    return response;
}
