/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:26:01 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/19 16:27:08 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/LocationHandler.hpp"

LocationHandler::LocationHandler(Config const &config) {
	this->config = config;
}

LocationHandler::run(HttpRequest request, HttpResponse response) {
	response.return(404);
}