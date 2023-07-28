#include "WebServ.hpp"

std::string IDENTIFIERS[] = {
		"listen",
		"server_name",
		"host",
		"root",
		"error_page",
		"allow_methods",
		"autoindex",
		"index",
		"return",
		"cgi_path",
		"cgi_ext"
};

std::string CONTEXTS[] = {
		"server",
		"location"
};

int main(int argc, char **argv) {

	if(argc != 2) {
		std::cout << "Invalid args" << std::endl;
		return (1);
	}


	std::ifstream configFile;

	configFile.open(argv[1]);

	new Core(configFile);
	//Core::deleteInstance();
	return (0);
}
