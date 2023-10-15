#include "WebServ.hpp"

HttpResponse::HttpResponse(void): type(GET) {

}

std::string HttpResponse::toString(void) {
	std::ostringstream data;
    data << "HTTP/1.1 " << this->statusCode << " OK\r\n";

    std::map<std::string, std::string>::iterator it;

    for (it = this->headers.begin(); it != this->end(); ++it) {
        int key = it->first;
        std::string value = it->second;
        data << it->first << ": " << it->second << "\r\n";
    }

    data << "\r\n" << this->body;
    return data.str();
}
