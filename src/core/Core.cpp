#include "WebServ.hpp"

/************** STATIC ******************/

//Core	*Core::getInstance(void)	{
//	return instance;
//}

/*void			Core::deleteInstance(void)	{
	delete instance;
	instance = 0;
}*/

/****************************************/



Core::Core(const std::ifstream &configFile) {
	try {
		std::vector<Handler *> handlers = ConfigParser::getHandlers(configFile);
		for(std::vector<Handler *>::iterator it = handlers.begin(); it != handlers.end(); it++) {
			this->servers.push_back(Server((ServerHandler *) *it));
		}
	} catch (const std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
	}
}

void Core::run() {
	for(std::vector<Server>::iterator it = this->servers.begin(); it != this->servers.end(); it++) {

	}
}

Core::~Core() {

}


std::vector<Server> const &Core::getServers(void) const {
	return (this->servers);
}

