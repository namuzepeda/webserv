#include "WebServ.hpp"

HttpRequest *HttpRequest::build(const std::string &buffer) {
	HttpRequest *request = new HttpRequest();
	(void) buffer;
	return request;
}

HttpRequest::HttpRequest(void): URI(0) {

}

HttpRequest::HttpRequest(const URI &uri, std::string body, RequestType type): uri(uri), body(body), type(type) {

}
