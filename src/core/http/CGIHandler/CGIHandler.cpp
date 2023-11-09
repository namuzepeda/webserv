/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:10:13 by gamoreno          #+#    #+#             */
/*   Updated: 2023/10/10 17:58:01 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

char **getEnvs(HttpRequest &request) {
    std::vector<std::string> envs;

    envs.push_back("QUERY_STRING=" + request.getQuery());
    envs.push_back("GATEWAY_INTERFACE=CGI/1.1");
    envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
    envs.push_back("REDIRECT_STATUS=200");
    envs.push_back("HTTP_HOST=" + request.getLocation());
    envs.push_back("REQUEST_METHOD=" + HttpUtils::getMethod(request.getType()));
    envs.push_back("SCRIPT_FILENAME=" + request.getFullPath());
    //envs.push_back("PATH_INFO=" + request.getFullPath());
    
    if(request.getConfig()->contains("upload_store"))
        envs.push_back("UPLOAD_STORE=" + request.getConfig()->get("upload_store"));
    envs.push_back("SCRIPT_NAME=" + request.getLocation());
    std::stringstream ss;
    
    // Insert the integer into the stringstream
    ss << request.getBody().length();

    envs.push_back("CONTENT_LENGTH=" + ss.str());
    if(request.headContains("Content-Type"))
        envs.push_back("CONTENT_TYPE=" + request.getHeadValue("Content-Type"));

    char **_ev = static_cast<char**>(malloc(sizeof(char *) * (envs.size() + 1)));
    for (size_t j = 0; j < envs.size(); j++)
	{
		_ev[j] = strdup(envs[j].c_str());
	}
	_ev[envs.size()] = 0;
	return _ev;
}

void replaceNewlineAndCarriageReturn(std::string& input) {
    size_t found = input.find("\n");
    while (found != std::string::npos) {
        input.replace(found, 1, "1");
        found = input.find("\n", found + 1);
    }

    found = input.find("\r");
    while (found != std::string::npos) {
        input.replace(found, 1, "0");
        found = input.find("\r", found + 1);
    }
}

std::string		CGIHandler::getResponse(HttpRequest &request, const Server *server)
{
	int out_pipe[2];
    int in_pipe[2];
    //int error_pipe[2];
    
    if (pipe(out_pipe) == -1) {
        request.setStatusCode(InternalServerError);
        return "ERROR";
    }

    if (request.getType() == POST && pipe(in_pipe) == -1) {
        close(out_pipe[0]);
        close(out_pipe[1]);
        request.setStatusCode(InternalServerError);
        return ("ERROR");
    }

    int errorFd = server->errors()->getFd();

    pid_t pid = fork();
    

    if (pid == 0) {

        
        if (request.getType() == POST) {
            close(in_pipe[1]);
            dup2(in_pipe[0], 0);
            close(in_pipe[0]);
        }

        close(out_pipe[0]);
        dup2(out_pipe[1], STDOUT_FILENO);
        close(out_pipe[1]);

        if(errorFd != -1)
            dup2(errorFd, STDERR_FILENO);

        char* argv[] = {(char *) strdup(request.getConfig()->get("cgi_pass").c_str()), (char *) strdup(request.getFullPath().c_str()), 0, 0};

        char **envs = getEnvs(request);

        execve(argv[0], argv, envs);

        exit(1);
    } else if (pid > 0) {

        close(out_pipe[1]);

        if (request.getType() == POST)
            close(in_pipe[0]);

        const int chunkSize = 512;
        const int bufferLength = request.getBody().length();
        int total = 0;
        for (int i = 0; i < bufferLength; i += chunkSize) {
            std::string chunk = request.getBody().substr(i, chunkSize);
            total += chunk.length();
            int wroten = write(in_pipe[1], chunk.c_str(), chunk.length());
            if(wroten == -1) {
                
            }
        }

        if (request.getType() == POST)
            close(in_pipe[1]);

        std::string cgi_output;
        char buffer[4096];
        ssize_t bytes_read;

        while ((bytes_read = read(out_pipe[0], buffer, sizeof(buffer))) > 0) {
            cgi_output.append(buffer, bytes_read);
        }

        cgi_output = cgi_output.substr(cgi_output.find("\n") + 1);
        
        close(out_pipe[0]);

        int status;
        waitpid(pid, &status, 0);

        if(status != 0) {
            request.setStatusCode(InternalServerError);
            return ("ERROR");
        }
        return (cgi_output);
    } else
        request.setStatusCode(InternalServerError);
    return ("ERROR");
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */