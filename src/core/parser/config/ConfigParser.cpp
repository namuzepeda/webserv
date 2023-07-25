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

#include "includes/ConfigParser.hpp"
#include "includes/WebServ.hpp"
#include "ConfigParserUtils.hpp"

std::string SkipWhitespace(const std::string& line) {
	size_t pos = line.find_first_not_of(" \t");
	return (pos != std::string::npos) ? line.substr(pos) : "";
}

Token GetNextToken(std::string& line) {
	line = SkipWhitespace(line);
	if (line.empty()) {
		return { TokenType::Invalid, "" };
	}

	if (ConfigParserUtils::isBlockStart(line[0])) {
		return { TokenType::BlockStart, std::string(1, line[0]) };
	}

	if (ConfigParserUtils::isBlockEnd(line[0])) {
		return { TokenType::BlockEnd, std::string(1, line[0]) };
	}

	if (ConfigParserUtils::isSemicolon(line[0])) {
		return { TokenType::Semicolon, std::string(1, line[0]) };
	}

	size_t pos = line.find_first_of(" \t;");
	if (pos == std::string::npos) {
		pos = line.length();
	}

	std::string tokenValue = line.substr(0, pos);
	line = line.substr(pos);
	if (ConfigParserUtils::isIdentifier(tokenValue)) {
		return {TokenType::Identifier, tokenValue};
	}
	else if (ConfigParserUtils::isValue(tokenValue)) {
		return {TokenType::Value, tokenValue};
	}

	return { TokenType::Invalid, "" };
}

const std::vector<Config> &ConfigParser::getConfigurations(std::ifstream configFile) const {
	std::vector<Config> configs;
	return (configs);
}

const std::vector<Token> parse(std::string &fileName) const {
	std::vector<Token> tokens;

	std::ifstream file(fileName);
	std::string line;

	while (std::getline(file, line)) {
		tokens.push_back(GetNextToken(line));
	}

	return (tokens);
}



















