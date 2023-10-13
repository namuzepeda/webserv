#include "WebServ.hpp"

HttpResponse::HttpResponse(HttpRequest const &requ)
: request(requ), statusCode(200)
{
	if (request.body.size() > limitRequestBody)
}

std::string HttpResponse::toString(void) {
	std::string string;
	return string;
}
