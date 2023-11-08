/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:03:32 by nmunoz            #+#    #+#             */
/*   Updated: 2023/10/17 17:45:37 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "WebServ.hpp"

class HttpResponse
{
	private:
		
		HttpStatusCode						statusCode;
		std::string							statusLine;
		std::map<std::string, std::string>	headers;
		std::string							body;
		std::string							finalResponse;
        std::map<int, std::string>          errorPages;
        bool                                isCgi;
        bool                                isDownload;
		
		HttpStatusCode	CheckRequestLine(const std::string& requestLine);
		// HttpStatusCode	IsUriValid(const std::string& uri);
		
		bool			goodQueryArgs(const std::string& query);

	public:

		HttpResponse(HttpRequest &request, bool isCgi);
		HttpResponse(HttpResponse const &copy);

		HttpResponse 	&operator=(HttpResponse const &copy);
		~HttpResponse();

        void        setBody(std::string body);

        std::string toString(HttpRequest &request);
		//get final response
	
};
/*
class HttpResponse {
public:
    // Constructor que toma una HttpRequest y otros argumentos necesarios
    HttpResponse(const HttpRequest& request,  otros argumentos ) : request_(request) {
        // Inicializa la respuesta HTTP
        status_code_ = 200;  // Código de estado de respuesta por defecto (OK).
        // Otros valores iniciales y configuraciones de encabezados, cuerpo, etc.
    }

    // Método para generar la respuesta HTTP como una cadena
    std::string toString() {
        std::string response;

        // 1. Genera la línea de estado (status line)
        std::string status_line = "HTTP/1.1 " + std::to_string(status_code_) + " " + getReasonPhrase(status_code_);
        response += status_line + "\r\n";

        // 2. Agrega encabezados HTTP
        // Debes configurar los encabezados necesarios basados en la solicitud y tus requerimientos.
        // Por ejemplo, puedes agregar un encabezado "Content-Type", "Content-Length", "Server", etc.
        // Utiliza la información de la solicitud y otros datos según sea necesario.

        // 3. Agrega una línea en blanco para separar encabezados y cuerpo
        response += "\r\n";

        // 4. Agrega el cuerpo de la respuesta si es necesario
        // El cuerpo puede ser HTML, texto, JSON, o cualquier otro contenido que desees enviar.

        return response;
    }

private:
    HttpRequest request_;
    int status_code_;  // Código de estado de la respuesta

    // Método para obtener la frase de estado (reason phrase) a partir del código de estado
    std::string getReasonPhrase(int status_code) {
        // Debes implementar una función que devuelva la frase de estado correspondiente al código.
        // Puedes definir un mapeo o una lista de códigos de estado y sus frases asociadas.
        // Por ejemplo, "200" se asocia a "OK".
        // "404" se asocia a "Not Found".
        // "500" se asocia a "Internal Server Error", y así sucesivamente.
        // Implementa este método según tus necesidades.
        return "";  // Reemplaza con la frase de estado correspondiente
    }
};

*/

#endif
