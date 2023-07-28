/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHolder.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/18 21:03:32 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HOLDER_H
#define LOCATION_HOLDER_H

#include "WebServ.hpp"

class LocationHolder : public Config
{
	public:

		LocationHolder(void);

		virtual					~LocationHolder();

		virtual ContextType		getType();
};

#endif
