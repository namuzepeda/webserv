/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:19:33 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
#define HANDLER_H

#include <set>
#include <iostream>
#include "Config.hpp"
#include <vector>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class Handler
{
	protected:

		std::set<Handler*>		childs;
		Config					*config;

	public:

		Handler(Config *config);
		virtual							~Handler();

		bool 							hasChilds();
		std::set<Handler *> 	const	&getChilds() const;

		Config							*getConfig();

		virtual void	 				run(const HttpRequest &request, const HttpResponse &response) = 0;

};

#endif
