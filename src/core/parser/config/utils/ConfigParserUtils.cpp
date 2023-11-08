#include "WebServ.hpp"


std::string ConfigParserUtils::IDENTIFIERS[] = {
		"listen",
		"server_name",
		"host",
		"root",
		"error_page",
		"allow_methods",
		"autoindex",
		"index",
		"return",
		"cgi_pass",
		"cgi_ext",
		"upload_store",
		"alias",
		"client_max_body_size",
		""
};

std::string ConfigParserUtils::CONTEXTS[] = {
		"server",
		"location",
		""
};


bool ConfigParserUtils::isBlockStart(char c) {
	return (c == '{');
}

bool ConfigParserUtils::isBlockEnd(char c) {
	return (c == '}');
}

bool ConfigParserUtils::isSemicolon(char c) {
	return (c == ';');
}

bool ConfigParserUtils::isComment(char c) {
	return (c == '#');
}

bool ConfigParserUtils::isIdentifier(const std::string &str) {
	if (str.empty())
		return false;

	return (StringArrayUtils::includes(IDENTIFIERS, str));
}

bool ConfigParserUtils::isContext(const std::string &str) {
	if (str.empty())
			return false;

	return (StringArrayUtils::includes(CONTEXTS, str));
}

bool ConfigParserUtils::isValue(const std::string &str) {
	if (str.empty())
		return false;
	return (!isIdentifier(str) && !isContext(str));
}

ContextType ConfigParserUtils::getContext(Token *token) {
	if(token->value == "server")
		return (SERVER);
	else
		return (LOCATION);
}

Handler	*ConfigParserUtils::getHandler(Config *config, std::string path, ContextType type) {
	switch(type) {
		case SERVER:
			return (new ServerHandler(config));
		default:
			return (new LocationHandler(config, path));
	}
}
