#include "server.h"
#include "request.h"
#include "logger.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;

void startServer() {
    Logger logger;
    struct sockaddr_in address;
    int server_fd, new_socket;
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        logger.log("Socket creation failed", "ERROR");
        std::cerr << "Socket failed" << std::endl;
        return;
    }
    logger.log("Socket created successfully", "INFO");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        logger.log("Setting SO_REUSEADDR socket option failed", "ERROR");
        std::cerr << "Setsockopt SO_REUSEADDR failed" << std::endl;
        return;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        logger.log("Setting SO_REUSEPORT socket option failed", "ERROR");
        std::cerr << "Setsockopt SO_REUSEPORT failed" << std::endl;
        return;
    }

    logger.log("Socket options set successfully", "INFO");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        logger.log("Binding socket failed", "ERROR");
        std::cerr << "Bind failed" << std::endl;
        return;
    }
    logger.log("Socket bound to port " + std::to_string(PORT), "INFO");

    if (listen(server_fd, 3) < 0) {
        logger.log("Listen failed", "ERROR");
        std::cerr << "Listen failed" << std::endl;
        return;
    }
    logger.log("Server is now listening on port " + std::to_string(PORT), "INFO");

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        logger.log("New connection accepted", "INFO");
        handleRequest(new_socket);
    }

    logger.log("Error accepting connection", "ERROR");
}
