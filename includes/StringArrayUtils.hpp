/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringArrayUtils.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/07/20 20:12:08 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_ARRAY_UTILS_H
#define STRING_ARRAY_UTILS_H

#include "WebServ.hpp"


class StringArrayUtils {

	public:

		static bool includes(std::string values[], const std::string &value);

};


#endif
