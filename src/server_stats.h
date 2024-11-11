#ifndef SERVER_STATS_H
#define SERVER_STATS_H

#include <string>
#include <unordered_map>
#include <mutex>

class ServerStats {
private:
    std::mutex statsMutex;
    std::unordered_map<std::string, int> pathHits;
    std::unordered_map<int, int> statusCodes;
    int totalRequests = 0;
    double totalResponseTime = 0.0;

public:
    void updateStats(const std::string& path, int statusCode, double responseTime);
    std::string getStatsHtml();
};

#endif
