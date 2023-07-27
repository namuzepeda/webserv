/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:22:03 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include "WebServ.hpp"

class ServerHandler : public Handler
{
	public:

		ServerHandler(Config *config);

		virtual					~ServerHandler();

		virtual void			run(const HttpRequest &request, const HttpResponse &response);
};

#endif
