#include "WebServ.hpp"

bool StringArrayUtils::includes(std::string values[], const std::string &value) {
	for(int i = 0; !values[i].empty(); i++) {
		if(values[i] == value)
			return (true);
	}
	return false;
}
