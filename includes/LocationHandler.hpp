/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationHandler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:22:03 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Handler.hpp"

class LocationHandler : public Handler
{
	public:

		LocationHandler(Config const &config);
		LocationHandler(LocationHandler const &copy);

		LocationHandler const	&operator=(LocationHandler const &copy);

		~LocationHandler();

		void			run(HttpRequest request);
};
