#include "WebServ.hpp"

bool ConfigParserUtils::isBlockStart(Token *token) {
	return (token->value[0] == '{');
}

bool ConfigParserUtils::isBlockEnd(Token *token) {
	return (token->value[0] == '}');
}

bool ConfigParserUtils::isSemicolon(Token *token) {
	return (token->value[0] == ';');
}

bool ConfigParserUtils::isIdentifier(Token *token) {
	if (token->value.empty())
		return false;

	return (StringArrayUtils::includes(IDENTIFIERS, token->value));
}

bool ConfigParserUtils::isContext(Token *token) {
	if (token->value.empty())
			return false;

	return (StringArrayUtils::includes(CONTEXTS, token->value));
}

bool ConfigParserUtils::isValue(Token *token) {
	if (token->value.empty())
		return false;
	return (!isBlockStart(token) && !isBlockEnd(token) && !isSemicolon(token) && !isIdentifier(token) && !isContext(token));
}

ContextType ConfigParserUtils::getContext(Token *token) {
	switch(token->value) {
		case "server":
			return (SERVER);
		default:
			return (LOCATION);
	}
}

Config *ConfigParserUtils::getHolder(ContextType type) {
	switch(ContextType type) {
		case SERVER:
			return (new ServerHolder());
		default:
			return (new LocationHolder());
	}
}

Handler	*ConfigParserUtils::getHandler(Config *config) {
	switch(config->getType()) {
		case SERVER:
			return (new ServerHandler(config));
		default:
			return (new LocationHandler(config));
	}
}
