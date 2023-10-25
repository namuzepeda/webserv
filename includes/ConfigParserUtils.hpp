/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:19:57 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:19:57 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_PARSER_UTILS_H
#define CONFIG_PARSER_UTILS_H

#include "WebServ.hpp"

class ConfigParserUtils
{
	public:

		static std::string 	IDENTIFIERS[];
		static std::string 	CONTEXTS[];

		static bool 		isBlockStart(char c);
		static bool 		isBlockEnd(char c);
		static bool 		isSemicolon(char c);
		static bool 		isComment(char c);
		static bool			isContext(const std::string &str);
		static bool 		isIdentifier(const std::string &str);
		static bool 		isValue(const std::string &str);

		static ContextType	getContext(Token *token) ;

		static Handler		*getHandler(Config *config, std::string path, ContextType type);

};

#endif



