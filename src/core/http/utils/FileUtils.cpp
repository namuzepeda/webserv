#include "WebServ.hpp"

bool    FileUtils::fileExists(const std::string &fileName) {
    return (access(fileName.c_str(), F_OK) == 0);
}

bool    FileUtils::canRead(const std::string &fileName) {
    return (access(fileName.c_str(), R_OK) == 0);
}