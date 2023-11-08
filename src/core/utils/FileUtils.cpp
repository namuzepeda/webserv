#include "WebServ.hpp"

bool    FileUtils::fileExists(const std::string &fileName) {
    return (access(fileName.c_str(), F_OK) == 0);
}

bool FileUtils::fileExists(const std::string &path, const std::string &fileName) {
    std::string totalPath = path + (path[path.length() - 1] != '/' && fileName[0] != '/' ? "/" : "") + fileName;
    return (FileUtils::fileExists(totalPath));
}

bool    FileUtils::canWrite(const std::string &fileName) {
    return (access(fileName.c_str(), W_OK) == 0);
}

bool    FileUtils::canRead(const std::string &fileName) {
    return (access(fileName.c_str(), R_OK) == 0);
}

bool FileUtils::canRead(const std::string &path, const std::string &fileName) {
    std::string totalPath = path + (path[path.length() - 1] != '/' && fileName[0] != '/' ? "/" : "") + fileName;
    return (FileUtils::canRead(totalPath));
}

std::string FileUtils::getFileData(const std::string &fileName) {
    std::ifstream file;
	file.open(fileName.c_str());
	if(!file.is_open())
        throw std::runtime_error("Cannot read data");

    std::string content;
	std::string fileLine;
	while (std::getline(file, fileLine)) {
		content += fileLine + '\n';
	}
    return (content);
}

std::string FileUtils::getFileData(const std::string &path, const std::string &fileName) {
    std::string totalPath = path + (path[path.length() - 1] != '/' && fileName[0] != '/' ? "/" : "") + fileName;
    return (FileUtils::getFileData(totalPath));
}

bool    FileUtils::isDirectory(const std::string &path) {
    struct stat fileInfo;
    if (stat(path.c_str(), &fileInfo) == 0) {
        return (S_ISDIR(fileInfo.st_mode));
    }
    throw new std::runtime_error("Cannot check if is directory");
}