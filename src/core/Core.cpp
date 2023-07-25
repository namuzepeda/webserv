#include "Core.hpp"
#include "ConfigParser.hpp"

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
	std::vector<Config> configs = ConfigParser::getConfigurations(configFile);
	for(std::vector<Config>::iterator it = configs.begin(); it != configs.end(); it++) {
		ServerHandler handler(*it);
		Server server(handler);
		this->servers.push_back(server);
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

