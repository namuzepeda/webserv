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

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

CGIHandler::CGIHandler(const &std::string ressource, const &std::string parameters)
:_resource(resource), _parameters(parameters)
{}

CGIHandler::CGIHandler( const CGIHandler & src )
{
    _resource = src.resource;
    _parameters = src.parameters;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

CGIHandler::~CGIHandler()
{}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

CGIHandler &				CGIHandler::operator=( CGIHandler const & rhs )
{
	if (this != &rhs)
	{
		_resource = rhs._resource;
		_parameters = rhs._parameter;
	}
	return *this;
}

// std::ostream &			operator<<( std::ostream & o, CGIHandler const & i )
// {
// 	//o << "Value = " << i.getValue();
// 	return o;
// }


/*
** --------------------------------- METHODS ----------------------------------
*/
std::string		CGIHandler::executeScript()
{
	int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        return "Error 500 (bad pipe)";
    }

    pid_t pid = fork();

    if (pid == 0) {
        setenv("QUERY_STRING", _parameters.c_str(), 1);

        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        char* script_path = (char*)_resource.c_str();
        char* script_argv[] = {script_path, nullptr};

        execve(script_path, script_argv, nullptr);

        exit(1);
    } else if (pid > 0) {
        close(pipe_fd[1]);

        // Read the output (STDOUT) of the CGI script from the read end of the pipe
        std::string cgi_output;
        char buffer[4096];
        ssize_t bytes_read;

        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            cgi_output.append(buffer, bytes_read);
        }

        close(pipe_fd[0]);

        int status;
        waitpid(pid, &status, 0);

        return cgi_output;
    } else {
        // Error when creating the child process
        // Handle the error
        return "Error 500 (creating child process)";
    }
}



/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */