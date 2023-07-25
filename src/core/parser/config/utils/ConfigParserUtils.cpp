#include "ConfigParserUtils.hpp"
#include "StringArrayUtils.hpp"
#include <string>
#include <iostream>

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
	if (!str || !*str)
		return false;

	return (StringArrayUtils::contains(IDENTIFIERS, str));
}
