/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:10:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/10/23 13:08:55y gamoreno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

void HttpRequest::cleanSpaces(std::string& line) {
	while (!line.empty() && (line[line.length() - 1] == '\r' || line[line.length() - 1] == '\n')) {
		line.erase(line.length() - 1);
	}
}

std::string replaceCarriageReturnAndNewline(const std::string &input) {
    std::string result;
    
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '\r') {
            result += '0';
        } else if (input[i] == '\n') {
            result += '1';
        } else {
            result += input[i];
        }
    }
    
    return result;
}


HttpRequest::HttpRequest(std::string &request, int serverSocket) : statusCode(Ok), config(new Config()), serverSocket(serverSocket) {
	try {
		std::string statusLine = request.substr(0, request.find("\n"));
		setLineParts(statusLine, type);

		std::string headerString;

		std::size_t pos = request.find("\r\n\r\n");

		if (pos != std::string::npos) {
			headerString = request.substr(0, pos);
		}

		if(headerString.length() > limitHeaderSize || InvalidHeaderChar(headerString)) {
			this->statusCode = BadRequest;
			throw std::runtime_error("Something wrong in request headers");
		}

		std::istringstream iss(headerString);
		std::string currLine;

		while (std::getline(iss, currLine)) {

			size_t separatorPos = currLine.find(": ");
			if(separatorPos != std::string::npos) {
				std::string headerName = currLine.substr(0, separatorPos);
				std::string currValue = currLine.substr(separatorPos + 2);
				cleanSpaces(currValue);
				std::string headerValue = currValue;
				if (noRepOfHeader(this->headers, headerName)) {
					this->headers[headerName] = headerValue;
				}
			}
		}

		setHostAndPort(this->headers);

		if (request.length() > pos + 4) {
			this->body = request.substr(pos + 4);
		}
	}
	catch (const std::exception &e) {
		std::cerr << "ERROR\n" << e.what() << std::endl;
		initVarErrorCase();
	}
}

HttpRequest::~HttpRequest(void) {
	delete this->config;
}

HttpRequest::HttpRequest(HttpRequest const &src)
{
	this->statusCode = src.statusCode;
	this->body = src.body;
	this->line = src.line;
	this->type = src.type;
	this->location = src.location;
	this->query = src.query;
	this->version = src.version;
	this->headers = src.headers;
	this->host = src.host;
	this->port = src.port;
	this->config = src.config;
}

HttpRequest &HttpRequest::operator=(HttpRequest const &rhs)
{
	if ( this != &rhs )
	{
		this->statusCode = rhs.statusCode;
		this->line = rhs.line;
		this->type = rhs.type;
		this->location = rhs.location;
		this->query = rhs.query;
		this->version = rhs.version;
		this->headers = rhs.headers;
		this->host = rhs.host;
		this->port = rhs.port;
		this->body = rhs.body;
		this->config = rhs.config;
	}
	return *this;
}

bool HttpRequest::noRepOfHeader(const std::map<std::string, std::string>& headers, const std::string& headerName) {
	for (std::map<std::string, std::string>::const_iterator iterator = headers.begin(); iterator != headers.end(); ++iterator) {
		if (compareNoCase(iterator->first, headerName) == 0) {
			return false;
		}
	}
	return true;
}

bool HttpRequest::compareNoCase(const std::string& str1, const std::string& str2) {
	if (str1.size() != str2.size()) {
		return true;
	}

	for (std::string::size_type i = 0; i < str1.size(); ++i) {
		if (std::tolower(str1[i]) != std::tolower(str2[i])) {
			return true;
		}
	}

	return false;
}

bool HttpRequest::InvalidHeaderChar(const std::string& headerLine) {
	const char* invalidChars = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
								"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";

	for (std::string::size_type i = 0; i < headerLine.length(); i++) {
		char c = headerLine[i];
		if (strchr(invalidChars, c) != NULL) {
			return true;
		}
	}

	return false;
}

void	HttpRequest::initVarErrorCase(void) {
	this->line = "error";
	this->location = "error";
	this->query = "error";
	this->version = "error";
	this->host = "error";
	this->port = -1;
	this->body = "error";
	this->type = NONE;
}

void	HttpRequest::setLineParts(std::string& line, RequestType& type){
	std::string::size_type	pos = line.find(' ');
	std::string::size_type	auxpos = pos + 1;

	cleanSpaces(line);
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
			throw std::runtime_error("Something wrong in request: not allowed method");
		}
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request not method found");
	}
	
	//handle URI
	pos = line.find(' ', auxpos);

	if (pos != std::string::npos) {
		std::string URI = line.substr(auxpos, pos - auxpos);
		if (URI.length() > limitUriSize) {
			this->statusCode = RequestUriTooLong;
			throw std::runtime_error("Something wrong in request URI to long");
		}
		for (std::string::size_type i = 0; i < URI.length(); i++) {
			char c = URI[i];

			if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.'
			|| c == '&' || c == '=' || c == '%' || c == '?' || c == '+')) {
				this->statusCode = BadRequest;
				throw std::runtime_error("Something wrong in request (invalid characters)");
			}
		}
		URI = decodeURI(URI);
		IsUriValid(URI);
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request invalid URI");
	}

	//Handle version
	auxpos = pos + 1;
	if (auxpos != std::string::npos) {
		this->version = line.substr(auxpos);
		if (this->version != "HTTP/1.1") {
			this->statusCode = VersionNotSupported;
			throw std::runtime_error("Something wrong in request version not supported");
		}
	}
	else {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request: no version found");
	}
}

bool HttpRequest::isValidHexDigit(char c) {
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

std::string HttpRequest::decodeURI(const std::string& encodedURI) {
	std::string decodedURI;
	for (std::size_t i = 0; i < encodedURI.length(); ++i) {
		if (encodedURI[i] == '%' && i + 2 < encodedURI.length()) {
			std::string hex = encodedURI.substr(i + 1, 2);
			if (isValidHexDigit(hex[0]) && isValidHexDigit(hex[1])) {
				char decodedChar = static_cast<char>(std::strtol(hex.c_str(), NULL, 16));
				decodedURI += decodedChar;
				i += 2;
			}
			else {
				this->statusCode = BadRequest;
				throw std::runtime_error("Something wrong in request invalid hexadecimal code character");
			}
		} else {
			decodedURI += encodedURI[i];
		}
	}
	return decodedURI;
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
		if (this->location.find('+') != std::string::npos) {
			this->statusCode = BadRequest;
			throw std::runtime_error("Something wrong in request: character '+' in location");
		}
		if (this->query.find('?') != std::string::npos) {
			this->statusCode = BadRequest;
			throw std::runtime_error("Something wrong in request: double '?'");
		}
	}
	if (!HttpRequest::goodQueryArgs(query)) {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request: wrong query");
	}
}

bool	HttpRequest::goodQueryArgs(const std::string& query) {
	bool	searchingForEq = true;
	bool	endAfterAmp = false;

	for (std::string::size_type i = 0; i < query.length(); i++) {
		char	c = query[i];

		//check existence of first word
		if (i == 0 && c == '=') 
			return false;

		if (searchingForEq) {
			if (c == '&')
				return false;
			else if(c == '=') {
				endAfterAmp = false;
				searchingForEq = false;
				if ((i == query.length() - 1) || (i < query.length() - 1 && query[i + 1] == '&'))
					return false;
			}
		}
		else if (!searchingForEq) {
			if (c == '=')
				return false;
			else if (c == '&') {
				endAfterAmp = true;
				searchingForEq = true;
				if ((i == query.length() - 1) || (i < query.length() - 1 && query[i + 1] == '='))
					return false;
			}
		}
	}
	if (endAfterAmp)
		return false;
	return true;
}

void HttpRequest::setHostAndPort(std::map<std::string, std::string>& headers){
	std::map<std::string, std::string>::iterator it = headers.find("Host");
	if (it == headers.end()) {
		this->statusCode = BadRequest;
		throw std::runtime_error("Something wrong in request variable Host not found");
	}
	std::string contentHostLine = it->second;

	std::string::size_type pos = contentHostLine.find(':');

	if (pos == std::string::npos){
		this->host = contentHostLine;
		this->port = 80;
	}
	else{
		this->host = contentHostLine.substr(0, pos);
		this->port = std::atoi(contentHostLine.substr(pos + 1).c_str());
	}
}

std::string	const &HttpRequest::getReqLine() const{
	return (this->line);
}

RequestType const &HttpRequest::getType() const{
	return (this->type);
}

std::string	const &HttpRequest::getLocation() const{
	return (this->location);
}

std::string	const &HttpRequest::getQuery() const{
	return (this->query);
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

int			HttpRequest::getPort() const{
	return (this->port);	
}

HttpStatusCode		HttpRequest::getStatusCode() {
	return (this->statusCode);
}

std::map<std::string, std::string> const &HttpRequest::getHeaders() const{
	return (this->headers);	
}

bool	HttpRequest::headContains(const std::string& key){
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

int 	HttpRequest::getServerSocket() const{
	return (this->serverSocket);
}

Config *HttpRequest::getConfig(void) const {
	return (this->config);
}

std::map<int, std::string> &HttpRequest::getErrorPages() {
	return (this->errorPages);
}

void HttpRequest::setStatusCode(HttpStatusCode code) {
	this->statusCode = code;
}

std::string HttpRequest::getFullPath() {

	std::string file;

	if(this->getLocation()[this->getLocation().length() - 1] == '/' && (!this->getConfig()->contains("autoindex") || this->getConfig()->get("autoindex") != "on"))
		file = HttpResponseUtils::getIndex(*this);
	else {
		file = this->getConfig()->get("root");
		file += this->getLocation();
	}

	return (file);
}

void	HttpRequest::setLocation(std::string location) {
	this->location = location;
}

std::ostream &operator<<(std::ostream &o, HttpRequest const &i)
{
	std::map<std::string, std::string>	currHeaders = i.getHeaders();
	
	o << "HttpRequest: \n\n";
	if (i.getType() == GET)
		std::cout << "type: GET" << "\n";
	if (i.getType() == POST)
		std::cout << "type: GET" << "\n";
	if (i.getType() == DELETE)
		std::cout << "type: GET" << "\n";
	std::cout << "location: " << i.getLocation() << "\n" \
	<< "version: " << i.getVersion() << "\n" \
	<< "Headers:\n" << std::endl;
	for (std::map<std::string, std::string>::iterator it = currHeaders.begin(); \
	it != currHeaders.end(); it++){

		o << it->first << " |U| " << it->second << std::endl;
	}
	
	o << "Body: " << i.getBody() << "\n\n" \
	<< "Host: " << i.getHost() << "\n" \
	<< "Port: " << i.getPort() << std::endl;
	
	return o;
}