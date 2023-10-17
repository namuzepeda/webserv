/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:10:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/10/17 18:02:22 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"


//copy constructor
//destructor
//asignement
HttpRequest::HttpRequest(const char * buffer) : statusCode(OK){
	std::string	Request = buffer;
	std::istringstream iss(Request);
	std::string currLine;
	
	try {
		std::getline(iss, line);
		setLineParts(line, type, location, version);

		while (std::getline(iss, currLine) && !currLine.empty()) {
			std::string::size_type separatorPos = currLine.find(": ");
			if (separatorPos != std::string::npos) {
				std::string headerName = currLine.substr(0, separatorPos);
				std::string headerValue = currLine.substr(separatorPos + 2);
			headers[headerName] = headerValue;
			}
		}

		setHostAndPort(headers, host, port);
	
		std::stringstream requestBodyStream;
		std::string bodyLine;
		while (std::getline(iss, bodyLine)) {
			requestBodyStream << bodyLine << '\n';
		}
		body = requestBodyStream.str();
	}
	catch (const std::exception &e) {
		initVarErrorCase();
		std::cerr << e.what() << std::endl;
	}
}

void	HttpRequest::initVarErrorCase(void) {
	this->line = "error";
	this->location = "error";
	this->query = "error";
	this->version = "error";
	this->host = "error";
	this->port = "error";
	this->body = "error";
	this->type = NONE;
}

void	HttpRequest::setLineParts(std::string& line, RequestType& type, std::string& location, std::string& version){
	std::string::size_type	pos = line.find(' ');
	std::string::size_type	auxpos = pos + 1;

	//Extract method
	if (pos != std::string::npos) {
		std::string aux = line.substr(0, pos);
		if (aux == "GET")
			type = GET;
		else if (aux == "POST")
			type = POST;
		else if (aux == "DELETE")
			type = DELETE;
		else {
			this->statusCode = MethodNotAllowed;
			throw std::runtime_error("Something wrong in request");
		}
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request");
	}

	//handle URI
	pos = line.find(' ', auxpos);
	if (pos != std::string::npos) {
		std::string URI = line.substr(auxpos, pos);
		IsUriValid(URI);
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request");
	}

	//Handle version
	auxpos = pos + 1;
	if (auxpos != std::string::npos) {
		version = line.substr(auxpos);
		if (version != "HTTP/1.1") {
			this->statusCode = VersionNotSupported;
			throw std::runtime_error("Something wrong in request");
		}
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request");
	}
	return ;
}

void HttpRequest::IsUriValid(const std::string& uri) {
	std::string::size_type queryStart = uri.find('?');

	if (queryStart == std::string::npos) {
		this->location = uri;
		this->query = "";
	}
	else {
		this->location = uri.substr(0, queryStart);
		this->query = uri.substr(queryStart + 1);
	}
	if (uri.length() > limitUriSize) {
		this->statusCode = RequestUriTooLong;
		throw std::runtime_error("Something wrong in request");
	}
	if (uri.find(' ') != std::string::npos) {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request");
	}
	for (std::string::size_type i = 0; i < location.length(); i++) {
		char c = location[i];
		if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.')) {
			this->statusCode = BadRequest;
			throw std::runtime_error("Something wrong in request");
		}
	}
	for (std::string::size_type i = 0; i < query.length(); i++) {
		char c = query[i];
		if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.'
		|| c == '&' || c == '=')) {
			this->statusCode = BadRequest;
			throw std::runtime_error("Something wrong in request");
		}
	}
	if (!HttpRequest::goodQueryArgs(query)) {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request");
	}
}

bool	HttpRequest::goodQueryArgs(const std::string& query) {
	//Checkar que todos los valores tengan parametro 
	return true;
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