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

std::string rightTrim(const std::string &input) {
    std::string trimmed = input;
    int i = trimmed.length() - 1;
    
    while (i >= 0 && std::isspace(trimmed[i])) {
        trimmed.erase(i, 1);
        i--;
    }
    
    return trimmed;
}

std::string SkipWhitespace(const std::string& line) {
	size_t pos = line.find_first_not_of(" \t");
	return (pos != std::string::npos) ? rightTrim(line.substr(pos)) : "";
}

void addToken(std::vector<Token *> &tokens, Token *token) {
	tokens.push_back(token);
}

void AddNextToken(std::vector<Token *> &tokens, std::string& line) {
	line = SkipWhitespace(line);
	if (line.empty() || ConfigParserUtils::isComment(line[0])) {
		return ;
	}
	
	if (ConfigParserUtils::isBlockStart(line[0])) {
		addToken(tokens, new Token(BLOCK_START, std::string(1, line[0])) );
		line = line.substr(1);
	}

	if (ConfigParserUtils::isBlockEnd(line[0])) {
		addToken(tokens, new Token(BLOCK_END, std::string(1, line[0])) );
		line = line.substr(1);
	}

	if (ConfigParserUtils::isSemicolon(line[0])) {
		addToken(tokens, new Token(SEMICOLON, std::string(1, line[0])) );
		line = line.substr(1);
	}

	size_t pos = line.find_first_of(" \t;#{}");
	if (pos == std::string::npos) {
		pos = line.length();
	}



	std::string tokenValue = SkipWhitespace(line.substr(0, pos));
	line = line.substr(pos);
	
	if (ConfigParserUtils::isIdentifier(tokenValue))
		addToken(tokens, new Token(IDENTIFIER, tokenValue) );

	if(ConfigParserUtils::isContext(tokenValue))
		addToken(tokens, new Token(CONTEXT, tokenValue));
	
	if (ConfigParserUtils::isValue(tokenValue))
		addToken(tokens, new Token(VALUE, tokenValue) );
	AddNextToken(tokens, line);
}

const std::vector<Token *> ConfigParser::parse(const std::ifstream &configFile) {
	std::vector<Token *> tokens;
	std::string line;

	while (std::getline((std::ifstream &) configFile, line)) {
		AddNextToken(tokens, line);
	}

	return (tokens);
}

std::vector<Handler *> ConfigParser::getHandlers(std::vector<Token *> &tokens) {
	std::vector<Handler *> handlers;
	std::vector<Handler *> tempHandlers;
	try {
		for(std::vector<Token *>::iterator it = tokens.begin(); it != tokens.end(); it++) {

			Handler *handler = tempHandlers.size() > 0 ? tempHandlers[tempHandlers.size() - 1] : NULL;

			if((*it)->type == BLOCK_END && handler != NULL) {
				tempHandlers.pop_back();
				if(tempHandlers.size() > 0)
					tempHandlers[tempHandlers.size() - 1]->addChild(handler);
				else
					handlers.push_back(handler);
			} else if ((*it)->type == CONTEXT) {
				ContextType contextType = ConfigParserUtils::getContext(*it);
				std::string value;
				it++;
				if((*it)->type == VALUE)
				{
					value = (*it)->value;
					it++;
				}
				if((*it)->type != BLOCK_START)
					throw std::runtime_error((*it)->value);
				tempHandlers.push_back(
						ConfigParserUtils::getHandler(
								new Config(), value, contextType
						)
				);
			} else if((*it)->type == IDENTIFIER && handler != NULL) {
				std::string identifier = (*it)->value;
				it++;
				if((*it)->type != VALUE)
					throw std::runtime_error((*it)->value);
				std::string value;
				while((*it)->type == VALUE) {
					value += (*it)->value;
					value += " ";
					it++;
				}
				if((*it)->type != SEMICOLON)
					throw std::runtime_error((*it)->value);
				handler->getConfig()->put(identifier, rightTrim(value));
			} else {
				throw std::runtime_error((*it)->value);
			}
		}
	} catch (const std::runtime_error &error) {
		for(std::vector<Handler *>::iterator it = tempHandlers.begin(); it != tempHandlers.end(); it++)
			delete *it;
		tempHandlers.clear();
		std::stringstream ss;
		ss << "Unexpected \"" << error.what() << "\"";
		throw std::runtime_error(ss.str());
	}
	for(std::vector<Handler *>::iterator it = tempHandlers.begin(); it != tempHandlers.end(); it++)
		delete *it;
	tempHandlers.clear();
	if(!handlers.size())
		throw std::runtime_error("There are no servers to be open");
	return (handlers);
}




















