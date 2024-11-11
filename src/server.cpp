#include "utils.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>

int main() {
    const int PORT = 8080;
    struct sockaddr_in address;
    int server_fd, new_socket;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "Socket failed" << std::endl;
        return -1;
    }

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        char buffer[30000] = {0};
        read(new_socket, buffer, 30000);

        // Convert buffer to a C++ string for easier handling
        std::string request(buffer);

        // Extract the path from the request line
        size_t method_end = request.find(" ");
        size_t path_end = request.find(" ", method_end + 1);
        std::string path = request.substr(method_end + 1, path_end - method_end - 1);

        std::cout << "Request received for path: " << path << std::endl;

        // Map URLs to file paths
        std::string file_path;
        if (path == "/") {
            file_path = "public/index.html";
        } else if (path == "/about") {
            file_path = "public/about.html";
        } else if (path == "/contact") {
            file_path = "public/contact.html";
        } else {
            // Try to serve the file directly from the public directory
            file_path = "public" + path;
        }

        // Read the file content
        std::string content = readFile(file_path);
        std::string response;

        if (!content.empty()) {
            std::string mime_type = getMimeType(file_path);
            response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: " + mime_type + "\r\n";
            response += "Content-Length: " + std::to_string(content.length()) + "\r\n";
            response += "\r\n";
            response += content;
        } else {
            // 404 response
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

        // Send the response to the client
        write(new_socket, response.c_str(), response.length());
        close(new_socket);
    }

    return 0;
}
