#include "../../includes/Core.hpp"

/************** STATIC ******************/

Core	const	&Core::getInstance(void) const	{
	return instance;
}

void			Core::deleteInstance(void) 		{
	delete instance;
	instance = 0;
}

/****************************************/

Core::Core(std::ifstream &configFile) {
	instance = this;


	if (! configFile.fail() )


}


