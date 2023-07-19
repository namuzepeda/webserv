/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHolder.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Config.hpp"

class ServerHolder : public Config
{
	protected:

		ServerHolder(void);
		ServerHolder(ServerHolder const &copy);

		ServerHolder const	&operator=(ServerHolder const &copy);

	public:

		virtual			~ServerHolder() {}

		bool 			hasChilds();
		ConfigType		getType();
};
