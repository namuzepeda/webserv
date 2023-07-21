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

#include "../../../../includes/ConfigParser.hpp"
#include "../../../includes/WebServ.hpp"
#include "../../../../includes/ConfigParserUtils.hpp"

std::string SkipWhitespace(const std::string& line) {
	size_t pos = line.find_first_not_of(" \t");
	return (pos != std::string::npos) ? line.substr(pos) : "";
}

Token GetNextToken(std::string& line) {
	line = SkipWhitespace(line);
	if (line.empty()) {
		return { TokenType::Invalid, "" };
	}

	if (ConfigParserUtils::IsBlockStart(line[0])) {
		return { TokenType::BlockStart, std::string(1, line[0]) };
	}

	if (ConfigParserUtils::IsBlockEnd(line[0])) {
		return { TokenType::BlockEnd, std::string(1, line[0]) };
	}

	if (ConfigParserUtils::IsSemicolon(line[0])) {
		return { TokenType::Semicolon, std::string(1, line[0]) };
	}

	if (std::regex_match(line, std::regex(R"(\d+)"))) {
		std::smatch match;
		std::regex_search(line, match, std::regex(R"(\d+)"));
		std::string value = match[0];
		line = line.substr(match.position(0) + value.length());
		return { TokenType::Value, value };
	}

	if (std::regex_match(line, std::regex(R"([a-zA-Z_]\w*)"))) {
		std::smatch match;
		std::regex_search(line, match, std::regex(R"([a-zA-Z_]\w*)"));
		std::string identifier = match[0];
		line = line.substr(match.position(0) + identifier.length());
		return { TokenType::Identifier, identifier };
	}

	return { TokenType::Invalid, "" };
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



















