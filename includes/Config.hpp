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

		std::map<std::string, std::vector<std::string> >	values;

	public:

		static const int	DEFAULT_BUFFER_SIZE = 1000000;

		Config(void);
		Config(Config const &copy);

		~Config();

		Config const	&operator=(Config const &copy);

		std::string 				get(const std::string &key);
		std::vector<std::string>	gets(const std::string &key);
		void						put(std::string key, std::string value);
		void						add(std::string key, std::string value);

		void 						remove(const std::string &key);
		bool						contains(const std::string &key);

		int							asInt(std::string key);


};

#endif
