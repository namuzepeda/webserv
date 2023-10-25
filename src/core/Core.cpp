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

std::string Core::getResponse(const HttpRequest &request) {
	std::cout << "0" << std::endl;
	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++) {
		Server *server = *it;
		std::cout << "1" << std::endl;
		if(ServerUtils::doesRequestApply(*server, request)) {
			std::cout << "2" << std::endl;
			server->getHandler()->run(request);
			HttpResponse response(request);
			return (response.toString());
		}
	}
	//response = HttpRequest();
	//response.statusCode = 400; //Bad request
	//return (response.toString());
	return (HttpResponseUtils::testResponse(InternalServerError, HttpResponseUtils::errorBody(InternalServerError)));
}

void	Core::run(void) {

	std::vector<int> sockets;

	for(std::vector<Server *>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		std::vector<int>::iterator findIt = std::find(sockets.begin(), sockets.end(), (*it)->getSocket());
		if(findIt == sockets.end()) { //No contiene socket
			sockets.push_back((*it)->getSocket());
		}
	}

	std::vector<int> clientSockets;
	std::vector<pollfd> pollEvents;

	while (!Core::stopped) {
		pollEvents.clear();

		//Esto se encarga del multiplexing
		for (std::vector<int>::iterator it = sockets.begin(); it != sockets.end(); it++) {
			int serverSocket = *it;
			pollfd serverEvent;
			serverEvent.fd = serverSocket;
			serverEvent.events = POLLIN;
			pollEvents.push_back(serverEvent);
		}

		for (size_t i = 0; i < clientSockets.size(); ++i) {
			pollfd clientEvent;
			clientEvent.fd = clientSockets[i];
			clientEvent.events = POLLIN | POLLOUT;
			pollEvents.push_back(clientEvent);
		}
		//std::cerr << "Before poll" << std::endl;
		int ready = poll(&pollEvents[0], pollEvents.size(), -1);
		//std::cerr << "Poll size: " << pollEvents.size() << std::endl;
		//std::cerr << "After poll" << std::endl;
		if (ready != -1) {
			//std::cerr << "Poll ready" << std::endl;
			for (size_t i = 0; i < sockets.size(); ++i) {
				if (pollEvents[i].revents & POLLIN) {
					sockaddr_in clientAddr;
					socklen_t clientAddrSize = sizeof(clientAddr);
					int clientSocket = accept(sockets[i], (struct sockaddr*)&clientAddr, &clientAddrSize);
					if (clientSocket == -1) {
						//std::cerr << "Error al aceptar la conexión." << std::endl;
					} else {
						//std::cout << "Conexión establecida con un cliente." << std::endl;

						int flags = fcntl(clientSocket, F_GETFL, 0);
						fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
						clientSockets.push_back(clientSocket);
					}
				}
			}
			//std::cerr << "Clients size: " << clientSockets.size() << std::endl;
			//std::cerr << "Poll size: " << pollEvents.size() << std::endl;
			//std::cerr << "0" << std::endl;
			for (size_t i = sockets.size(); i < pollEvents.size(); ++i) {
				//std::cerr << "01" << std::endl;
				if ((pollEvents[i].revents & POLLIN) || (pollEvents[i].revents & POLLOUT)) {
					//std::cerr << "02" << std::endl;
					char buffer[Config::DEFAULT_BUFFER_SIZE] = {0};
					int bytesRead = recv(pollEvents[i].fd, buffer, sizeof(buffer) + 1, 0);
					//std::cerr << "1" << std::endl;
					if (bytesRead <= 0) {
						//std::cerr << "2" << std::endl;
						// El cliente ha cerrado la conexión o ha ocurrido un error
						clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), pollEvents[i].fd), clientSockets.end());
						close(pollEvents[i].fd);
						//std::cout << "Conexión cerrada con un cliente." << std::endl;

						// Eliminar el socket del cliente del vector de clientes
						
					} else {
						//std::cerr << "3" << std::endl;
						// Procesar la solicitud del cliente
						buffer[bytesRead] = '\0'; // Asegurarnos de terminar el buffer como una cadena de caracteres
						HttpRequest request(buffer);

						std::string response = getResponse(request);
						
						//std::cerr << "Returning response " << std::endl << responseString << std::endl;
						//std::cout << "returning response " << std::endl << responseString.c_str() << std::endl;
						send(pollEvents[i].fd, response.c_str(), response.length(), 0);
						/*HttpResponse *response = getResponse(request);
						if(response) {
							std::string responseString = response->toString();
							send(pollEvents[i].fd, responseString.c_str(), responseString.length(), 0);
						}
						if(!request.headContains("Keep-alive")) {
							clientSockets.erase(clientSockets.begin() + i - 1);
						}*/
					}
					//std::cerr << "4" << std::endl;
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

