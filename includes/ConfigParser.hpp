/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:19:57 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:19:57 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "WebServ.hpp"
#include "Config.hpp"

class ConfigParser {

	public:

		static const std::vector<Config> &getConfigurations(std::ifstream configFile) const;

};


#endif
