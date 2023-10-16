/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:10:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/10/16 18:58:31 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

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

void setHostAndPort(std::map<std::string, std::string>& headers, std::string host, std::string port){
	std::map<std::string, std::string>::iterator it = headers.find("Host");
	std::string contentHostLine = it->second;
	std::string::size_type pos = contentHostLine.find(':');

	if (pos == std::string::npos){
		host = contentHostLine;
		port = "8080";
	}
	else{
		host = contentHostLine.substr(0, pos);
		port = contentHostLine.substr(pos + 1);
	}
}

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

	// Extract host and port from headers
	setHostAndPort(headers, host, port);
	
    std::stringstream requestBodyStream;
	std::string bodyLine;
	while (std::getline(iss, bodyLine)) {
		requestBodyStream << bodyLine << '\n';
	}
	body = requestBodyStream.str();
}


HttpRequest::~HttpRequest() {

}

std::string	const &HttpRequest::getReqLine() const{
	return (this->line);
}

std::string const &HttpRequest::getType() const{
	return (this->type);
}

std::string	const &HttpRequest::getLocation() const{
	return (this->location);
}

std::string	const &HttpRequest::getParameters() const{
	return (this->parameters);
}

std::string	const &HttpRequest::getVersion() const{
	return (this->version);
}

std::string	const &HttpRequest::getBody() const{
	return (this->body);
}	

std::string	const &HttpRequest::getHost() const{
	return (this->host);
}

std::string const &HttpRequest::getPort() const{
	return (this->port);	
}

std::map<std::string, std::string> const &HttpRequest::getHeaders() const{
	return (this->headers);	
}

bool		HttpRequest::headContains(const std::string& key){
	std::map<std::string, std::string>::iterator it = headers.find(key);
	if (it != headers.end())
		return (true);
	return (false);
}

std::string	HttpRequest::getHeadValue(const std::string& key){
	std::string ret;
	std::map<std::string, std::string>::iterator it = headers.find(key);
	
	if (it != headers.end())
		ret = it->second;
	return (ret);
}

std::ostream &operator<<(std::ostream &o, HttpRequest const &i)
{
	std::map<std::string, std::string>	currHeaders = i.getHeaders();
	
	o << "HttpRequest: \n\n" \
	<< "type: " << i.getType() << "\n" \
	<< "location: " << i.getLocation() << "\n" \
	<< "version: " << i.getVersion() << "\n" \
	<< "Headers:\n" << std::endl;
	for (std::map<std::string, std::string>::iterator it = currHeaders.begin(); \
	it != currHeaders.end(); it++){
		o << it->first << ':' << it->second << std::endl;
	}
	
	o << "Body: " << i.getBody() << "\n\n" \
	<< "Host: " << i.getHost() << "\n" \
	<< "Port:" << i.getPort() << std::endl;
	
	return o;
}