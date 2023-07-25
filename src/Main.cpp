#include "../includes/WebServ.hpp"
#include "../includes/Core.hpp"



int main(int argc, char **argv) {

	if(argc != 2) {
		std::cout << "Invalid args" << std::endl;
		return (1);
	}

	new Core(std::ifstream(argv[1]));
	Core::deleteInstance();
	return (0);
}
