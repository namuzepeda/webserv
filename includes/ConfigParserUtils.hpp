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

#include "../../../includes/ConfigParser.hpp"

class ConfigParserUtils
{
	public:

		static bool isBlockStart(char ch);
		static bool isBlockEnd(char ch);
		static bool isSemicolon(char ch);
		static bool isIdentifier(const std::string &str);
		static bool isValue(const std::string &str);

};

#endif



