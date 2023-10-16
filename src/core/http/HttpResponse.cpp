#include "WebServ.hpp"

HttpResponse::HttpResponse(HttpRequest const &requ)
: request(requ), statusCode(200)
{
	int	auxStatus;

	if (request.getBody().size() > limitRequestBody) {
		statusCode = 413;
		HttpResponse::buildResponse();
		return;
	}
	auxStatus = CheckRequestLine(request.getReqLine());
	if (auxStatus != statusCode) {
		statusCode = auxStatus;
		HttpResponse::buildResponse();
	}

	//if get push delete

}

HttpResponse::HttpResponse(HttpResponse const &copy){
	//pendiente
}

HttpResponse 	&HttpResponse::operator=(HttpResponse const &copy) {
	//pendiente
}

HttpResponse::~HttpResponse() {
	//pendiente
}

int	HttpResponse::CheckRequestLine(const std::string& requestLine) {
	std::istringstream	stream(requestLine);
	std::string			method, uri, version;

	if (!(stream >> method) || stream.get() != ' ' || !(stream >> uri) || stream.get() != ' ' || !(stream >> version)) {
		return 404; 
	}
	if ((method != "GET" && method != "POST" && method != "DELETE")) {
		return 404;
	}
	if (!HttpResponse::IsUriValid(uri)) {
		return 404;
	}
	if (version != "HTTP/1.1") {
		return 505;
	}
	if (method != request.getType() || version != request.getVersion()) {
		return 500;
	}
	return 200;
}

bool HttpResponse::IsUriValid(const std::string& uri) {
	for (std::string::size_type i = 0; i < uri.length(); i++) {
		char c = uri[i];
		if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.')) {
			return false;
		}
	}

	if (uri.find(' ') != std::string::npos) {
		return false;
	}

	return true;
}

std::string HttpResponse::toString(void) {
	std::string string;
	return string;
}

void	HttpResponse::buildResponse(void) {
	if (statusCode != 200) {
		//inicializar otros valores de forma estandar 
		finalResponse = ErrorMessage(statusCode); //por cuadrar bien
	}
	else
		finalResponse = toString();
}

std::string HttpResponse::GetStatusMessage(int statusCode) {
    std::string message;
    
    switch (statusCode) {
        case 200:
            message = "OK";
            break;
        case 201:
            message = "Created";
            break;
        case 400:
            message = "Bad Request";
            break;
        case 404:
            message = "Not Found";
            break;
        case 413:
            message = "Request Entity Too Large";
            break;
		case 500:
			message = "Internal Server Error";
			break;
		case 505:
			message = "Version Not Supported";
			break;
        default:
            message = "Unknown Status";
            break;
    }

    return message;
}