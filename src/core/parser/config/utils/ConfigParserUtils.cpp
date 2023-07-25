#include "../../../includes/ConfigParserUtils.hpp"

bool ConfigParserUtils::IsBlockStart(char ch) {
	return (ch == '{');
}

bool ConfigParserUtils::IsBlockEnd(char ch) {
	return (ch == '}');
}

bool ConfigParserUtils::IsSemicolon(char ch) {
	return (ch == ';');
}

bool
