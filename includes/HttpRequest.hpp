/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/17 16:21:19by gamoreno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "WebServ.hpp"

class HttpRequest
{
	private:

		HttpStatusCode						statusCode;
		std::string							line;
		RequestType							type;
		std::string							location;
		std::string							query;
		std::string							version;
		std::map<std::string, std::string>	headers;
		std::string							host;
		int									port;
		std::string							body;
		Config								*config;
		std::map<int, std::string>          errorPages;
	

	void		setLineParts(std::string& line, RequestType& type);
	void		initVarErrorCase(void);
	bool		goodQueryArgs(const std::string& query);
	bool		isValidHexDigit(char c);
	std::string	decodeURI(const std::string& encodedURL);
	void		IsUriValid(const std::string& uri);
	bool		InvalidHeaderChar(const std::string& headerLine);
	bool		noRepOfHeader(const std::map<std::string, std::string>& headers, const std::string& headerName);
	bool		compareNoCase(const std::string& str1, const std::string& str2);
	void		setHostAndPort(std::map<std::string, std::string>& headers);
	void		cleanSpaces(std::string& line);



	public:

		HttpRequest(const char *buffer);
		HttpRequest(HttpRequest const &src);
		~HttpRequest();
		HttpRequest &operator=(HttpRequest const &rhs);

		std::string	const &getReqLine() const;
		RequestType	const &getType() const;
		std::string	const &getLocation() const;
		std::string	const &getQuery() const;
		std::string	const &getVersion() const;
		std::string	const &getBody() const;
		HttpStatusCode		getStatusCode();
		std::map<std::string, std::string>	const &getHeaders() const;
		bool		headContains(const std::string& key);
		std::string	getHeadValue(const std::string& key);
		std::string	const &getHost() const;
		int			getPort() const;
		Config		*getConfig(void) const;
		std::map<int, std::string> 	 &getErrorPages();
		
		std::string getFullPath();

		void		setLocation(std::string location);

		void		setStatusCode(HttpStatusCode code);

};

std::ostream &operator<<(std::ostream &o, HttpRequest const &i);

#endif