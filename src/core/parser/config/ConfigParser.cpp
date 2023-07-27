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
		return new Token(Invalid, "");
	}

	if (ConfigParserUtils::isBlockStart(line[0])) {
		return new Token(BlockStart, std::string(1, line[0]));
	}

	if (ConfigParserUtils::isBlockEnd(line[0])) {
		return new Token(BlockEnd, std::string(1, line[0]));
	}

	if (ConfigParserUtils::isSemicolon(line[0])) {
		return new Token(Semicolon, std::string(1, line[0]));
	}

	size_t pos = line.find_first_of(" \t;");
	if (pos == std::string::npos) {
		pos = line.length();
	}

	std::string tokenValue = line.substr(0, pos);
	line = line.substr(pos);
	if (ConfigParserUtils::isIdentifier(tokenValue)) {
		return new Token(Identifier, tokenValue);
	}
	else if (ConfigParserUtils::isValue(tokenValue)) {
		return new Token(Value, tokenValue);
	}

	return new Token( Invalid, "" );
}

std::vector<Config *> ConfigParser::getConfigurations(const std::ifstream &configFile) {
	std::vector<Config *> configs;
	(void) configFile;
	return (configs);
}

const std::vector<Token *> parse(std::string &fileName) {
	std::vector<Token *> tokens;

	std::ifstream file;
	std::string line;

	file.open(fileName.c_str());

	while (std::getline(file, line)) {
		tokens.push_back(GetNextToken(line));
	}

	return (tokens);
}



















