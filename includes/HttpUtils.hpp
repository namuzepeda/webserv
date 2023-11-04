/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpUtils.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/16 19:24:09 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include "WebServ.hpp"


class HttpUtils {
	
	public:

		static std::string	getMethod(RequestType type);
		static long			getContentLength(const std::string &buffer);
		static long			getBodyLength(const std::string& httpRequest);

};


#endif
