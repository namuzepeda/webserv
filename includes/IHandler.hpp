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

#ifndef IHANDLER_H
#define IHANDLER_H

#include <iostream>
#include <set>
#include "Config.hpp"
#include <vector>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

enum ContextType {
	SERVER
};


class IHandler
{
	public:

		virtual								~IHandler();

		virtual bool 						hasChilds() 					= 0;
		virtual std::set<IHandler>	const	&getChilds() const				= 0;

		virtual	Config 				const	&getConfig() const 				= 0;

		virtual	ContextType					getType() 						= 0;

		virtual void	 					run(const HttpRequest &request, const HttpResponse &response) = 0;

};


#endif
