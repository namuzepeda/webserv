#include "WebServ.hpp"

bool ConfigParserUtils::isBlockStart(char ch) {
	return (ch == '{');
}

bool ConfigParserUtils::isBlockEnd(char ch) {
	return (ch == '}');
}

bool ConfigParserUtils::isSemicolon(char ch) {
	return (ch == ';');
}

bool ConfigParserUtils::isIdentifier(const std::string &str) {
	if (str.empty())
		return false;

	return (StringArrayUtils::includes(IDENTIFIERS, str));
}

bool ConfigParserUtils::isValue(const std::string &str) {
	if (str.empty())
		return false;
	return true;
}
