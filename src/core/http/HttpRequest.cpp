#include "WebServ.hpp"

HttpRequest::HttpRequest(const URI &uri, std::string body, RequestType type): URI(uri), body(body), type(type) {

}
