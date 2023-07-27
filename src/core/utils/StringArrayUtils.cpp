#include "WebServ.hpp"

bool StringArrayUtils::includes(std::string values[], const std::string &value) {
	int size = sizeof(std::string *) / sizeof(std::string);
	for (int i = 0; i < size; ++i) {
		if (values[i] == value)
			return true;
	}
	return false;
}
