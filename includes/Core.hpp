/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Cluster.hpp"

class Core
{
	private:

		static Core	instance;


		std::vector<Server>	ports;

	public:

		static Core	const	&getInstance(void) const;
		static void			deleteInstance(void);


		Core(std::ifstream configFile);
		Core(Core const &copy);

		Core const			&operator=(Server const &copy);
		virtual				~Core();

		std::vector<Server> const	&getServers(void) const;s

};
