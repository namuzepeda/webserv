#include "WebServ.hpp"
#include "../includes/Core.hpp"
#include <fstream>

int main(int argc, char **argv) {

	if(argc != 2) {
		std::cout << "Invalid args" << std::endl;
		return (1);
	}

	std::string arg1(argv[1]);

	new Core(arg1);
	//Core::deleteInstance();
	return (0);
}
