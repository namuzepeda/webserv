/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHandler.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:24:06 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <set>
#include "Config.hpp"
#include <vector>

enum ContextType {
	SERVER
};


class IHandler
{
	public:

		virtual								~IHandler();

		virtual	ContextType const			getType() const 	= 0;

		virtual	Config const				&getConfig() const 	= 0;

		virtual bool 						hasChilds() 		= 0;
		virtual std::set<Handler*> const	&getChilds() const	= 0;

		virtual void	 					run() 				= 0;

};
