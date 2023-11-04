#include "WebServ.hpp"

/************** STATIC ******************/

/*void			Core::deleteInstance(void)	{
	delete instance;
	instance = 0;
}*/

/****************************************/



Core::Core(const std::ifstream &configFile) {
	std::vector<Token *> tokens = ConfigParser::parse(configFile);
	try {
		std::vector<Handler *> handlers = ConfigParser::getHandlers(tokens);
		for(std::vector<Handler *>::iterator it = handlers.begin(); it != handlers.end(); it++) {
			Server *server = new Server((ServerHandler *) *it);
			InitType initType = server->init(this->servers, 3);
			if(initType == SUCCESS) {
				this->servers.push_back(server);
				std::cerr << "SUCCESS" << std::endl;
			} else {
				delete server;
				std::cerr << "ERROR " << initType << std::endl;
			}
		}
		handlers.clear();
		run();
	} catch (const std::runtime_error &error) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
	for(std::vector<Token *>::iterator it = tokens.begin(); it != tokens.end(); it++) {
		Token *token = *it;
		delete token;
	}
	tokens.clear();
}

Core::~Core() {
	for (std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); ++it) {
		Server *server = *it;
		delete server;
	}
	this->servers.clear();
}

std::string Core::getResponse(HttpRequest &request) {

	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++) {
		Server *server = *it;
		if(ServerUtils::doesRequestApply(*server, request)) {
			server->getHandler()->run(request);
			HttpResponse response(request, request.getConfig()->contains("cgi_pass"));
			return (response.toString(request));
		}
	}
	return (HttpResponseUtils::testResponse(InternalServerError, HttpResponseUtils::errorBody(InternalServerError)));
}

void	Core::run(void) {

	std::vector<int> sockets;
	std::vector<pollfd> pollEvents;
	std::map<int, pollconn> pollConnections;

	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		std::vector<int>::iterator findIt = std::find(sockets.begin(), sockets.end(), (*it)->getSocket());
		if(findIt == sockets.end()) { //No contiene socket
			sockets.push_back((*it)->getSocket());
			pollfd serverEvent;
			serverEvent.fd = (*it)->getSocket();
			serverEvent.events = POLLIN;
			pollEvents.push_back(serverEvent);
		}
	}

	std::vector<int> clientSockets;

	while (!Core::stopped) {
		pollEvents.erase(pollEvents.begin() + sockets.size(), pollEvents.end());
		for (size_t i = 0; i < clientSockets.size(); ++i) {
			pollfd clientEvent;
			clientEvent.fd = clientSockets[i];
			clientEvent.events = POLLIN | POLLOUT;
			pollEvents.push_back(clientEvent);
		}
		//std::cout << "Before poll" << std::endl;
		int ready = poll(&pollEvents[0], pollEvents.size(), -1);
		//std::cout << "After poll" << std::endl;
		if (ready != -1) {
			for (size_t i = 0; i < sockets.size(); ++i) {
				if (pollEvents[i].revents & POLLIN) {
					sockaddr_in clientAddr;
					socklen_t clientAddrSize = sizeof(clientAddr);
					int clientSocket = accept(sockets[i], (struct sockaddr*)&clientAddr, &clientAddrSize);
					if (clientSocket == -1) {
						std::cerr << "Error al aceptar la conexión." << std::endl;
					} else {
						std::cout << "Conexión establecida con un cliente." << std::endl;
						int flags = fcntl(clientSocket, F_GETFL, 0);
						fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
						clientSockets.push_back(clientSocket);
					}
				}
			}
			for (size_t i = sockets.size(); i < pollEvents.size(); ++i) {
				if ((pollEvents[i].revents & POLLIN)) {
					char buffer[4096] = {0};
					int bytesRead = recv(pollEvents[i].fd, buffer, 4096, 0);
					struct timeval currentTime;
					gettimeofday(&currentTime, NULL);
					long long time = currentTime.tv_sec * 1000LL + currentTime.tv_usec;
					pollConnections[pollEvents[i].fd].lastInteraction = time;
					pollConnections[pollEvents[i].fd].differentRead = bytesRead != 4096;
					if(bytesRead != 4096)
						std::cout << "DIFFERENT BYTES" << std::endl;
					if (bytesRead == -1 || bytesRead == 0) {
						clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
						close(pollEvents[i].fd);
						ClientConnection::deleteBuffer(pollEvents[i].fd);
						std::cout << "Conexión cerrada con un cliente." << std::endl;
					} else {
						std::string sBuffer(buffer, bytesRead);
						ClientConnection::requests[pollEvents[i].fd] += sBuffer;
					}
				} else {
					std::map<int, pollconn>::iterator it = pollConnections.find(pollEvents[i].fd);
					if(it != pollConnections.end()) {
						if(pollConnections[pollEvents[i].fd].differentRead && ClientConnection::isRequestCompleted(pollEvents[i].fd)) {
							HttpRequest request(ClientConnection::getBuffer(pollEvents[i].fd).c_str());
							std::string response = getResponse(request);
							send(pollEvents[i].fd, response.c_str(), response.length(), 0);
							ClientConnection::deleteBuffer(pollEvents[i].fd);
							close(pollEvents[i].fd);
							std::cout << "Conexión cerrada con un cliente. ELSE IF" << std::endl;
							clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
							pollConnections.erase(it);
						}
					}
				}
			}
		} else {
			if(!Core::stopped)
				std::cerr << "Error en la función poll()." << std::endl;
		}
	}

	// Cerrar los sockets de los clientes que aún estén abiertos
	for (size_t i = 0; i < clientSockets.size(); ++i) {
		std::cout << "Closing client socket !" << std::endl;
		close(clientSockets[i]);
	}

	// Cerrar los sockets del servidor
	for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
		int serverSocket = *it;
		std::cout << "Closing server socket !" << std::endl;
		close(serverSocket);
	}
}

std::vector<Server *> const &Core::getServers(void) const {
	return (this->servers);
}

