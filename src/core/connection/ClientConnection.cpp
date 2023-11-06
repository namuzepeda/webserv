#include "WebServ.hpp"

std::map<int, std::string> ClientConnection::requests;

bool ClientConnection::isChunkedRequest(int socket) {
    std::string buffer = ClientConnection::requests[socket];

    return (buffer.find("Content-Length: ") == std::string::npos && buffer.find("Transfer-Encoding: chunked") != std::string::npos);
}

bool ClientConnection::isRequestCompleted(int socket) {
    if(!isChunkedRequest(socket)) {
        int contentLength = HttpUtils::getContentLength(ClientConnection::requests[socket]);
        if(contentLength == 0)
            return (true);
        int bodyLength = HttpUtils::getBodyLength(ClientConnection::requests[socket]);
        if(bodyLength == -1)
            return (false);
        return (contentLength == bodyLength);
    }
        

    std::string buffer = ClientConnection::requests[socket];
    return (buffer.substr(buffer.length() - 5) == "0\r\n\r\n");
}

void    ClientConnection::deleteBuffer(int socket) {
    std::map<int, std::string >::iterator it = ClientConnection::requests.find(socket);
    if (it != ClientConnection::requests.end()) {
        ClientConnection::requests.erase(it);
    }
}

bool ClientConnection::hasBuffer(int socket) {
    return ClientConnection::requests.find(socket) != ClientConnection::requests.end();
}

std::string ClientConnection::getBuffer(int socket) {
    std::string buffer = ClientConnection::requests[socket];

    if(!isChunkedRequest(socket))
        return (buffer);
    if(!isRequestCompleted(socket))
        throw std::runtime_error("Buffer is not completed");
    std::string	headers = buffer.substr(0, buffer.find("\r\n\r\n"));
    std::string	rest    = buffer.substr(buffer.find("\r\n\r\n") + 4, buffer.size() - 1);
    std::string	subchunk = rest.substr(0, 100);
	std::string	body = "";
	int			chunksize = strtol(subchunk.c_str(), NULL, 16);
	size_t		i = 0;

	while (chunksize)
	{
		i = rest.find("\r\n", i) + 2;
		body += rest.substr(i, chunksize);
		i += chunksize + 2;
		subchunk = rest.substr(i, 100);
		chunksize = strtol(subchunk.c_str(), NULL, 16);
	}
    return (headers + "\r\n\r\n" + body + "\r\n\r\n");
}