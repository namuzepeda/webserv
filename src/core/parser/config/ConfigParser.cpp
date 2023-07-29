/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:16:06 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:16:06 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

std::string SkipWhitespace(const std::string& line) {
	size_t pos = line.find_first_not_of(" \t");
	return (pos != std::string::npos) ? line.substr(pos) : "";
}

Token *GetNextToken(std::string& line) {
	line = SkipWhitespace(line);
	if (line.empty()) {
		return new Token(INVALID, "");
	}

	if (ConfigParserUtils::isBlockStart(line[0])) {
		return new Token(BLOCK_START, std::string(1, line[0]));
	}

	if (ConfigParserUtils::isBlockEnd(line[0])) {
		return new Token(BLOCK_END, std::string(1, line[0]));
	}

	if (ConfigParserUtils::isSemicolon(line[0])) {
		return new Token(SEMICOLON, std::string(1, line[0]));
	}

	size_t pos = line.find_first_of(" \t;");
	if (pos == std::string::npos) {
		pos = line.length();
	}

	std::string tokenValue = line.substr(0, pos);
	line = line.substr(pos);
	if (ConfigParserUtils::isIdentifier(tokenValue)) {
		return new Token(IDENTIFIER, tokenValue);
	}
	else if(ConfigParserUtils::isContext(line)) {
		return new Token(CONTEXT, tokenValue);
	} else if (ConfigParserUtils::isValue(tokenValue)) {
		return new Token(VALUE, tokenValue);
	}

	return new Token( INVALID, "" );
}

const std::vector<Token *> parse(const std::ifstream &configFile) {
	std::vector<Token *> tokens;
	std::string line;

	while (std::getline((std::ifstream &) configFile, line)) {
		tokens.push_back(GetNextToken(line));
	}

	return (tokens);
}

std::vector<Handler *> ConfigParser::getHandlers(const std::ifstream &configFile) {
	std::vector<Handler *> handlers;
	std::vector<Token *> tokens = parse(configFile);

	std::vector<Handler *> tempHandlers;

	for(std::vector<Token *>::iterator it = tokens.begin(); it != tokens.end(); it++) {

		Handler *handler = tempHandlers.size() ? tempHandlers[tempHandlers.size() - 1] : NULL;


		if((*it)->type == BLOCK_END && handler != NULL) {
			tempHandlers.pop_back();
			if(tempHandlers.size() > 0)
				tempHandlers[tempHandlers.size() - 1]->addChild(handler);
			else
				handlers.push_back(handler);
		} else if ((*it)->type == CONTEXT) {
			ContextType contextType = ConfigParserUtils::getContext(*it);
			std::string value = 0;
			it++;
			if((*it)->type == VALUE)
			{
				value = (*it)->value;
				it++;
			}

			if((*it)->type != BLOCK_START)
				throw std::runtime_error("Error on configuration file");
			tempHandlers.push_back(
					ConfigParserUtils::getHandler(
							ConfigParserUtils::getHolder(contextType), value
					)
			);
		} else if((*it)->type == IDENTIFIER && handler != NULL) {
			std::string identifier = (*it)->value;
			it++;
			if((*it)->type != VALUE)
				throw std::runtime_error("Error on configuration file");
			std::string value = (*it)->value;
			it++;
			if((*it)->type != SEMICOLON)
				throw std::runtime_error("Error on configuration file");
			handler->getConfig()->put(identifier, value);
		} else {
			throw std::runtime_error("Error on configuration file");
		}
	}
	return (handlers);
}




















