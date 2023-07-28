#include "WebServ.hpp"

HttpRequest *HttpRequest::build(const std::string &buffer) {
	HttpRequest *request = new HttpRequest();
	return request;
}

HttpRequest::HttpRequest(void): type(0) {

}

HttpRequest::HttpRequest(const URI &uri, std::string body, RequestType type): URI(uri), body(body), type(type) {

}
