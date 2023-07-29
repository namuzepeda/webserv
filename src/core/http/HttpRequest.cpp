#include "WebServ.hpp"

HttpRequest::HttpRequest(const char * buffer){
	std::string	Request = buffer;
	std::istringstream iss(Request);
    std::string currLine;

	// Extract the request line
    std::getline(iss, line);

    // red the headers and set the mapm
    while (std::getline(iss, currLine) && !currLine.empty()) {
        std::string::size_type separatorPos = currLine.find(": ");
        if (separatorPos != std::string::npos) {
            std::string headerName = currLine.substr(0, separatorPos);
            std::string headerValue = currLine.substr(separatorPos + 2);

            // Assign header to map
            headers[headerName] = headerValue;
        }
    }

    // set the body
    body = iss.str().substr(iss.tellg());
}

HttpRequest::~HttpRequest() {

}

std::string	const &HttpRequest::getReqLine() const{
	return(line);
}

std::string const &getType() const{

}
std::string							const &getLocation() const;
std::string							const &getVersion() const;
std::map<std::string, std::string>	const &getHeaders() const;
std::string							const &getbody() const;	
