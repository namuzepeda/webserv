# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 16:55:18 by gamoreno          #+#    #+#              #
#    Updated: 2023/07/25 16:41:55 by gamoreno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
NAME		=	webserv
CC			=	c++
FLAGS		=	-Wall -Wextra -Werror -g3 -std=c++98 
INCLUDES	=	-I $(HEADER)

###  PATHS ###
SRC_PATH	=	src/
HEADER		=	includes/
OBJ_PATH	=	objs/

### FILES ###
CORE_DIR					=	core/
CORE						= 	Core.cpp

CONFIG_DIR					=	core/config/
CONFIG						=	Config.cpp

CONFIG_HOLD_DIR				=	core/config/holders/
CONFIG_HOLD					=	ServerHolder.cpp

HANDLER_DIR					=	core/handlers/
HANDLER						=	Handler.cpp \
								ServerHandler.cpp \
								LocationHandler.cpp \
								
HTTP_DIR					=	core/http/
HTTP						=	HttpRequest.cpp \
								HttpResponse.cpp

PARSER_CONFIG_DIR			=	core/parser/config/
PARSER_CONFIG				=	ConfigParser.cpp

PARSER_CONFIG_UTILS_DIR		=	core/parser/config/utils/
PARSER_CONFIG_UTILS			=	ConfigParserUtils.cpp

SERVER_DIR					=	core/server/
SERVER						=	Server.cpp

SERVER_UTILS_DIR			=	core/server/utils/
SERVER_UTILS				=	ServerUtils.cpp

UTILS_DIR					=	core/utils/
UTILS						=	FileUtils.cpp StringArrayUtils.cpp

OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(HTTP_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CORE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CONFIG_HOLD_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(HANDLER_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(PARSER_CONFIG_UTILS_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(SERVER_UTILS_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(UTILS_DIR))

SOURCES		+=	$(addprefix	$(HTTP_DIR),$(HTTP))
SOURCES		+=	$(addprefix	$(CONFIG_DIR),$(CONFIG))
SOURCES		+=	$(addprefix	$(CONFIG_HOLD_DIR),$(CONFIG_HOLD))
SOURCES		+=	$(addprefix	$(HANDLER_DIR),$(HANDLER))
SOURCES		+=	$(addprefix	$(PARSER_CONFIG_DIR),$(PARSER_CONFIG))
SOURCES		+=	$(addprefix	$(PARSER_CONFIG_UTILS_DIR),$(PARSER_CONFIG_UTILS))
SOURCES		+=	$(addprefix	$(SERVER_DIR),$(SERVER))
SOURCES		+=	$(addprefix	$(UTILS_DIR),$(UTILS))
SOURCES		+=	$(addprefix	$(SERVER_UTILS_DIR),$(SERVER_UTILS))
SOURCES		+=	$(addprefix	$(CORE_DIR),$(CORE))
SOURCES		+=	Main.cpp
				
### FILE MANAGEMENT ###
SRCS		=	$(addprefix $(SRC_PATH),$(SOURCES))
OBJS		=	$(addprefix $(OBJ_PATH),$(SOURCES:.cpp=.o))
DEPS		=	$(addprefix $(OBJ_PATH),$(SOURCES:.cpp=.d))	

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###

all: tmp $(NAME)


tmp:
		@mkdir -p $(OBJ_DIRS)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
		echo "$(GREEN) Compilation succesfully.$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(RM) $(OBJ_PATH)
		echo "$(GREEN) Non-executable files removed.$(NOC)"
	
fclean: clean
		@$(RM) $(NAME)
		@echo "$(GREEN) Executable removed$(NOC)"

re: fclean all

RM			=	rm -rf

-include $(DEPS)

.PHONY: all clean fclean re 
