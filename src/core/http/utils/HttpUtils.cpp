#include "WebServ.hpp"

std::string HttpUtils::getMethod(RequestType type) {
    switch(type) {
        case GET:
            return ("GET");
        case POST:
            return ("POST");
        case DELETE:
            return ("DELETE");
        default:
            throw std::runtime_error("Method not supported");
    }
}

long HttpUtils::getContentLength(const std::string &buffer) {
    std::size_t pos = buffer.find("\r\n\r\n");
    if (pos == std::string::npos) {
        return -1;
    }
    std::string sub = buffer.substr(0, pos);
    pos = sub.find("Content-Length: ");
    if (pos == std::string::npos) {
        return -1;
    }
    sub = sub.substr(pos + 16);
    pos = sub.find("\r\n");
    if(pos != std::string::npos)
        sub = sub.substr(0, pos);
    return std::atoi(sub.c_str());
}

long HttpUtils::getBodyLength(const std::string& buffer) {
    //std::cout << "SizeE! " << buffer.length() << std::endl;
    return (buffer.size());
}