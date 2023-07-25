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

}

void Core::run() {
	ConfigParser parser(configFile);
}

Core::~Core() {

}


std::vector<Server> const &Core::getServers(void) const {
	return (this->servers);
}

