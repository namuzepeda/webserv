#include "WebServ.hpp"
#include "../includes/Core.hpp"
#include <fstream>

int main(int argc, char **argv) {

	if(argc != 2) {
		std::cout << "Invalid args" << std::endl;
		return (1);
	}
;

	std::ifstream configFile;

	configFile.open(argv[1]);

	new Core(configFile);
	//Core::deleteInstance();
	return (0);
}
