/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:22:03 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HANDLER_H
#define LOCATION_HANDLER_H

#include "WebServ.hpp"

class LocationHandler : public Handler
{
	public:

		LocationHandler(Config *config);

		virtual					~LocationHandler();

		virtual void			run(const HttpRequest &request, const HttpResponse &response);
};

#endif
