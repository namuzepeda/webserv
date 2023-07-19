/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHandler.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Config.hpp"

class IHandler
{
	protected:

		IHandler(void);
		IHandler(IHandler const &copy);

		IHandler const			&operator=(IHandler const &copy);

	public:

		virtual					~IHandler() {}

		virtual void 			run() = 0;
		virtual	Config const	&getConfig() const = 0;
};
