#include "utils.h"
#include <fstream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string getFilePath(const string &path) {
    if (path == "/") {
        return "public/index.html";
    } else if (path == "/about") {
        return "public/about.html";
    } else if (path == "/contact") {
        return "public/contact.html";
    } else {
        return "public" + path;
    }
}

string getMimeType(const string& filename) {
    static map<string, string> mimeTypes;
    if (mimeTypes.empty()) {
        mimeTypes[".html"] = "text/html; charset=utf-8";
        mimeTypes[".css"] = "text/css; charset=utf-8";
        mimeTypes[".js"] = "application/javascript; charset=utf-8";
        mimeTypes[".jpg"] = "image/jpeg";
        mimeTypes[".jpeg"] = "image/jpeg";
        mimeTypes[".png"] = "image/png";
        mimeTypes[".gif"] = "image/gif";
        mimeTypes[".svg"] = "image/svg+xml";
        mimeTypes[".json"] = "application/json";
        mimeTypes[".pdf"] = "application/pdf";
        mimeTypes[".txt"] = "text/plain; charset=utf-8";
    }

    size_t dot_pos = filename.find_last_of(".");
    if (dot_pos != string::npos) {
        string ext = filename.substr(dot_pos);
        map<string, string>::iterator it = mimeTypes.find(ext);
        if (it != mimeTypes.end()) {
            return it->second;
        }
    }
    return "application/octet-stream";
}
