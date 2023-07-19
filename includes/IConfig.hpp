/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IConfig.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

enum ConfigType {
	SERVER
};

class IConfig
{
	protected:

		IConfig(void);
		IConfig(IConfig const &copy);

		IConfig const		&operator=(IConfig const &copy);

	public:

		virtual				~IConfig() {}

		virtual bool 		hasChilds() = 0;
		virtual	bool		getChilds() = 0;

		virtual	ConfigType	getType() = 0;
};
