#include "WebServ.hpp"

HttpResponse::HttpResponse(HttpRequest const &requ)
: request(requ), statusCode(Ok)
{
	std::string fileName = this->request.getConfig()->get("root");
	std::string location = this->request.getLocation();

	if(location != "/")
		fileName += location;
	else if(this->request.getConfig()->contains("index")) {
		
	} else {
		fileName += "/index.html";
	}
		

	std::cout << "File to read: " << fileName << std::endl;

	if(!FileUtils::fileExists(fileName)) {
		this->statusCode = NotFound;
		return ;
	}

	if(!FileUtils::canRead(fileName)) {
		this->statusCode = Forbidden;
		return ;
	}

	std::ifstream file;
	file.open(fileName.c_str());
	if(!file.is_open()) {
		this->statusCode = InternalServerError;
		return ;
	}

	std::string fileLine;
	while (std::getline(file, fileLine)) {
		this->body += fileLine + '\n';
	}
    
	std::cout << this->body << std::endl;

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

std::string HttpResponse::toString(void) {

	std::stringstream responseStream;
    responseStream << "HTTP/1.1 " << statusCode << " " << HttpResponseUtils::getStatus(this->statusCode) << "\r\n";
    responseStream << "Content-Type: text/html\r\n";
    responseStream << "\r\n"; // Fin de las cabeceras, línea en blanco

	if(this->statusCode == 200)
		responseStream << this->body;
	else
		responseStream << HttpResponseUtils::errorBody(this->statusCode);
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
