#include "server_stats.h"
#include <sstream>

void ServerStats::updateStats(const std::string& path, int statusCode, double responseTime) {
    std::lock_guard<std::mutex> lock(statsMutex);
    pathHits[path]++;
    statusCodes[statusCode]++;
    totalRequests++;
    totalResponseTime += responseTime;
}

std::string ServerStats::getStatsHtml() {
    std::lock_guard<std::mutex> lock(statsMutex);
    std::stringstream ss;
    ss << "<h2>Server Statistics</h2>";
    ss << "<p>Total Requests: " << totalRequests << "</p>";
    ss << "<p>Average Response Time: " << (totalRequests > 0 ? totalResponseTime / totalRequests : 0) << "ms</p>";

    ss << "<h3>Path Hits:</h3><ul>";
    for (const auto& [path, hits] : pathHits) {
        ss << "<li>" << path << ": " << hits << "</li>";
    }
    ss << "</ul>";

    ss << "<h3>Status Codes:</h3><ul>";
    for (const auto& [code, count] : statusCodes) {
        ss << "<li>" << code << ": " << count << "</li>";
    }
    ss << "</ul>";

    return ss.str();
}
