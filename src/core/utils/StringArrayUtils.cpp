#include "StringArrayUtils.hpp"

StringArrayUtils::contains(std::string *values, const std::string &value) {
	for (const std::string *ptr = *values; *ptr != 0; ++ptr) {
		if (*ptr == value)
			return true;
	}
	return false;
}
