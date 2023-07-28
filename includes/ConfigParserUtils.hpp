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

		static bool 		isBlockStart(Token *token);
		static bool 		isBlockEnd(Token *token);
		static bool 		isSemicolon(Token *token);
		static bool			isContext(Token *token);
		static bool 		isIdentifier(Token *token);
		static bool 		isValue(Token *token);

		static ContextType getContext(Token *token) ;

		static Config 		*getHolder(ContextType type);
		static Handler		*getHandler(Config *config);

};

#endif



