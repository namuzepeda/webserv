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

#include <map>
#include <iostream>

class Config
{
	protected:

		std::map<std::string, std::string>	values;

	public:

		Config(void);
		Config(Config const &copy);

		Config const	&operator=(Config const &copy);
		virtual			~Config() {}

		bool	contains(std::string key);

		std::string get(std::string key);
		std::string	put(std::string key, std::string value);


};

#endif
