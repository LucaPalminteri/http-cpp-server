#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string readFile(const std::string& filename);
std::string getFilePath(const std::string &path);
std::string getMimeType(const std::string& filename);

#endif
