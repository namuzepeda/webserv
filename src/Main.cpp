#include "WebServ.hpp"

bool Core::stopped = false;

std::map<HttpStatusCode, std::string> HttpResponseUtils::statusMap;

void	sighandler(int signum)
{
	(void) signum;
	std::cout << "Stoping server" << std::endl;
	Core::stopped = true;
}

int main(int argc, char **argv) {

	signal(SIGINT, sighandler);

	if(argc != 2) {
		std::cout << "Invalid args" << std::endl;
		return (1);
	}

	HttpResponseUtils::initStatusMap();

	std::ifstream configFile;

	configFile.open(argv[1]);

	Core *core = new Core(configFile);
	delete core;
	return (0);
}
