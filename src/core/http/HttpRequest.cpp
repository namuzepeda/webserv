#include "WebServ.hpp"

HttpRequest::HttpRequest(const char * buffer){
	std::string	Request = buffer;
	std::istringstream iss(Request);
    std::string currLine;

	// Extract the request line
    std::getline(iss, line);

    // Fill variables
    setLineParts(line, type, location, version);
    
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

void    setLineParts(std::string& line, std::string& type, std::string& location, std::string& version){
	std::string::size_type	pos = line.find(' ');
	std::string::size_type	auxpos = pos + 1;
	if (pos != std::string::npos) {
		type = line.substr(0, pos);
	}
	pos = line.find(' ', auxpos);
	if (pos != std::string::npos) {
		location = line.substr(auxpos, pos);
	}
	auxpos = pos + 1;
	if (auxpos != std::string::npos) {
		version = line.substr(auxpos);
	}
	return ;
}

HttpRequest::~HttpRequest() {

}

std::string	const &HttpRequest::getReqLine() const{
	return (this->line);
}

std::string const &getType() const{
	return (this->type);
}

std::string	const &getLocation() const{
	return (this->location);
}

std::string	const &getVersion() const{
	return (this->version);
}

std::string	const &getBody() const{
	return (this->body);
}	

bool		HttpRequest::headContains(const std::string& key){

	for	(std::map<std::string, std::string>::iterator it = this->headers.begin(), it != this->headers; it++){
		if (it->first = key)
			return(true);
	}
	return (false);
}

std::string	const &HttpRequest::getHeadValue(const std::string& key) const{
	std::map<std::string, std::string>::iterator it = this->headers.find(key)
	return(it != this->headers.end() ? it->second : NULL);
}

std::string	const &HttpReauest::getHost() const{

}

std::string const &HttpRequest::getPort() const{
	
}


