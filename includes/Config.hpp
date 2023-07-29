/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
#define CONFIG_H

#include "WebServ.hpp"

class Config
{

	protected:

		std::map<std::string, std::string>	values;

	public:

		static const int	DEFAULT_BUFFER_SIZE = 1000000;

		Config(void);
		Config(Config const &copy);

		Config const	&operator=(Config const &copy);
		virtual			~Config();

		std::string get(std::string key);
		std::string	put(std::string key, std::string value);

		bool		contains(std::string key);

		int			asInt(std::string key);

		bool		hasMaxBodySize();
		int			getMaxBodySize();

		virtual	ContextType			getType()						= 0;


};

#endif
