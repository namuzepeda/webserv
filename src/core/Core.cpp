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
	(void) configFile;
	ServerHolder holderr(void);
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

