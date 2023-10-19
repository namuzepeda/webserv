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

	private:

		std::string				path;

	public:

		LocationHandler(Config *config, std::string path);

		virtual					~LocationHandler();

		virtual void			run(const HttpRequest &request);

		std::string				getPath();
};

#endif
