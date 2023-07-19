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

#pragma once

#include "IConfig.hpp"
#include <map>

class Config: public IConfig
{
	protected:

		std::map<std::string, std::string>	values;

	public:

		Config(void);
		Config(Config const &copy);

		Config const	&operator=(Config const &copy);
		virtual			~Config() {}

};
