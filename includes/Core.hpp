#ifndef CORE_H
#define CORE_H

#include "Cluster.hpp"

class Core
{
	private:

		static Core	*instance;


		std::vector<Server>	servers;

	public:


		//static void			deleteInstance(void);


		Core(const std::ifstream &configFile);
		virtual ~Core();

		std::vector<Server> const 	&getServers(void) const;

		virtual	ContextType			getType()						= 0;

		void						run();

};

#endif
