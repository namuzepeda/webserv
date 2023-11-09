#include "WebServ.hpp"


void replace(std::string& str, const std::string &find, const std::string &replace) {
    size_t pos = 0;
    while ((pos = str.find(find, pos)) != std::string::npos) {
        str.replace(pos, find.length(), replace);
        pos += replace.length();
    }
}


HttpResponse::HttpResponse(HttpRequest  &request, bool isCgi, const Server *server): statusCode(Ok), isCgi(isCgi), isDownload(false)
{

	if(request.getStatusCode() != Ok) {
		this->statusCode = request.getStatusCode();
		return ;
	}

	if (request.getBody().length() > (unsigned long) (request.getConfig()->contains("client_max_body_size") ? request.getConfig()->asInt("client_max_body_size") : 8120000)) {
		this->statusCode = RequestEntityTooLarge;
		return ;
	}

	if(request.getConfig()->contains("return")) {
		this->statusCode = MovedPermanently;
		this->headers["Location"] = request.getConfig()->get("return");
		return ;
	}

	if (!request.getConfig()->contains("root") && !request.getConfig()->contains("alias")) {
		this->statusCode = InternalServerError;
		return ;
	}

	if(!HttpResponseUtils::isMethodAllowed(request)) {
		this->statusCode = MethodNotAllowed;
		return ;
	}

	std::string file = "";

	if(request.getConfig()->contains("alias")) {
		file = request.getConfig()->get("alias");
		std::size_t pos = request.getLocation().find("/");
		file += request.getLocation().substr(pos != std::string::npos ? pos : 0);
	} else {
		file = request.getConfig()->get("root") + request.getLocation();
	}

	replace(file, "//", "/");

	if(!this->isCgi) {
		if(request.getType() == DELETE) {
			if(FileUtils::fileExists(request.getFullPath()) && !FileUtils::isDirectory(request.getFullPath())) {
				if (remove(request.getFullPath().c_str()) == 0) {
					this->statusCode = NoContent;
				} else {
					this->statusCode = Forbidden;
				}
			} else {
				this->statusCode = MethodNotAllowed;
			}
			return ;
		}
	}

	if(!FileUtils::fileExists(file)) {
		this->statusCode = NotFound;
		return ;
	}

	if(!FileUtils::canRead(file)) {
		this->statusCode = Forbidden;
		return ;
	}

	if(FileUtils::isDirectory(file)) {
		if(request.getLocation()[request.getLocation().length() - 1] != '/') {
			this->statusCode = MovedPermanently;
			this->headers["Location"] = request.getLocation()[0] == '/' ? request.getLocation() : "/" + request.getLocation() + "/";
			return ;
		}
		this->body = HttpResponseUtils::getDirectoryResponse(file);
		return ;
	}

	if(this->isCgi) {
		this->body = CGIHandler::getResponse(request, server);
		if(this->body == "ERROR")
			this->statusCode = InternalServerError;
		return ;
	} else {
		try {
			this->body = FileUtils::getFileData(file);
		} catch (std::runtime_error &e) {
			this->statusCode = InternalServerError;
			return ;
		}
	}
	size_t pos = request.getLocation().find_last_of(".");
	if(pos != std::string::npos) {
		std::string type = request.getLocation().substr(pos, request.getLocation().length());
		if(type != ".html")
			this->isDownload = true;
	}
	 
}

void        HttpResponse::setBody(std::string body) {
	this->body = body;
}

/*HttpResponse::HttpResponse(HttpResponse const &copy){
	//pendiente
}

HttpResponse 	&HttpResponse::operator=(HttpResponse const &copy) {
	//pendiente
}*/

HttpResponse::~HttpResponse() {
	//pendiente
}

// HttpStatusCode	HttpResponse::CheckRequestLine(const std::string& requestLine) {
// 	std::istringstream	stream(requestLine);
// 	std::string			method, uri, version;
// 	HttpStatusCode		aux;

// 	if (!(stream >> method) || stream.get() != ' ' || !(stream >> uri) || stream.get() != ' ' || !(stream >> version)) {
// 		return BadRequest; 
// 	}
// 	if ((method != "GET" && method != "POST" && method != "DELETE")) {
// 		return MethodNotAllowed;
// 	}
// 	aux = HttpResponse::IsUriValid(uri);
// 	if (aux != 200) {
// 		return aux;
// 	}
// 	if (version != "HTTP/1.1") {
// 		return VersionNotSupported;
// 	}
// 	if (method != this->request.getType() || version != this->request.getVersion()) {
// 		return InternalServerError;
// 	}

		
// 	return OK;
// }

// bool	HttpResponse::goodQueryArgs(const std::string& query) {
// 	//Checkar que todos los valores tengan parametro 
// 	return true;
// }

// HttpStatusCode HttpResponse::IsUriValid(const std::string& uri) {
// 	std::string	location, query;
// 	std::string::size_type queryStart = uri.find('?');

// 	if (queryStart == std::string::npos) {
// 		location = uri;
// 		query = "";
// 	}
// 	else {
// 		location = uri.substr(0, queryStart);
// 		query = uri.substr(queryStart + 1);
// 	}
// 	if (uri.length() > limitUriSize) {
// 		return RequestUriTooLong;
// 	}
// 	if (uri.find(' ') != std::string::npos) {
// 		return BadRequest;
// 	}
// 	for (std::string::size_type i = 0; i < location.length(); i++) {
// 		char c = location[i];
// 		if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.')) {
// 			return BadRequest;
// 		}
// 	}
// 	for (std::string::size_type i = 0; i < query.length(); i++) {
// 		char c = query[i];
// 		if (!(isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.'
// 		|| c == '?' || c == '&' || c == '=')) {
// 			return BadRequest;
// 		}
// 	}
// 	if (!HttpResponse::goodQueryArgs(query))
// 		return BadRequest;
// 	return OK; // La URI es válida
// }

std::string HttpResponse::toString(HttpRequest &request) {

	std::stringstream responseStream;
    responseStream << "HTTP/1.1 ";

	size_t pos = this->body.find_first_of("\r\n");

	if (this->isCgi && this->statusCode == Ok) {
		if(this->body.substr(0, 7) == "Status:")
			responseStream << this->body.substr(8, pos - 8);
		else
			responseStream << "200 Ok";
	} else {
		responseStream << statusCode << " " << HttpResponseUtils::getStatus(this->statusCode) ;
	}
	responseStream << "\r\n";

	if(this->isDownload) {
		responseStream << "Content-Type: application/octet-stream\r\n";
		responseStream << "Content-Disposition: attachment; filename=" << request.getLocation().substr(request.getLocation().find_last_of("/") + 1, request.getLocation().length()) << "\r\n";
	}
	

	if(this->isCgi && this->statusCode == Ok) {
		responseStream << this->body;
		return (responseStream.str());
	}
	else
		responseStream << "Content-Type: text/html\r\n";
	for (std::map<std::string, std::string>::iterator it = this->headers.begin(); it != this->headers.end(); ++it) {
		responseStream << it->first << ": " << it->second << "\r\n";
    }
    responseStream << "\r\n"; // Fin de las cabeceras, línea en blanco

	if(this->statusCode == Ok)
		responseStream << this->body;
	else if(this->statusCode != MovedPermanently && this->statusCode != NoContent) {
		std::map<int, std::string >::iterator it = request.getErrorPages().find(this->statusCode);
		if(it != request.getErrorPages().end()
			&& FileUtils::fileExists(request.getConfig()->get("froot"), it->second)
			&& FileUtils::canRead(request.getConfig()->get("froot"), it->second)) {
			responseStream << FileUtils::getFileData(request.getConfig()->get("froot"), it->second);
		} else
			responseStream << HttpResponseUtils::errorBody(this->statusCode);
	}
		
/*
    std::map<std::string, std::string>::iterator it;

    for (it = this->headers.begin(); it != this->end(); ++it) {
        int key = it->first;
        std::string value = it->second;
        data << it->first << ": " << it->second << "\r\n";
    }

    data << "\r\n" << this->body;*/ //crear funcion que settee el buen body si es OK o si es error y los headers
    return responseStream.str();
}
