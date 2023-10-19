/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponseUtils.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:12:08 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/16 19:24:09 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_UTILS_H
#define HTTP_RESPONSE_UTILS_H

#include "WebServ.hpp"


class HttpResponseUtils {

  private:

		static std::map<HttpStatusCode, std::string> statusMap;

	
	public:

		static void		initStatusMap(void);
		static std::string getStatus(HttpStatusCode code);
		static std::string testResponse(HttpStatusCode statusCode, std::string body);
		static std::string errorBody(HttpStatusCode responseCode);

};


#endif
