#include "WebServ.hpp"

bool Core::stopped = false;

std::map<HttpStatusCode, std::string> HttpResponseUtils::statusMap;

void	sighandler(int signum)
{
	(void) signum;
	Logger::info->log(StringUtils::parse("\n[WebServ] Closing WebServ\n").c_str());
	Core::stopped = true;
}

int main(int argc, char **argv) {

	signal(SIGINT, sighandler);
	signal(SIGPIPE, SIG_IGN);

	if(argc != 2) {
		std::cout << "Invalid args: ./webserv {config}" << std::endl;
		return (1);
	}

	HttpResponseUtils::initStatusMap();

	std::ifstream configFile;

	configFile.open(argv[1]);

	Core *core = new Core(configFile);
	delete core;
	return (0);
}
