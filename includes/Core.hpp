#ifndef CORE_H
#define CORE_H

#include "WebServ.hpp"

class Core
{
	private:

		std::vector<Server *>	servers;

	public:


		static bool					stopped;

		static Core					*getInstance(void);


		Core(const std::ifstream &configFile);
		virtual 					~Core();

		std::vector<Server *> const &getServers(void) const;

		std::string					getResponse(const HttpRequest &request);
		void						run(void);

};

#endif
