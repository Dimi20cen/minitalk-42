# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 14:46:47 by dmylonas          #+#    #+#              #
#    Updated: 2021/10/04 21:03:05 by dmylonas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -g

LIB_PATH = ./Libft
LIB_NAME = libft.a

NAME = client
NAME_1 = server

CLIENT_SRCS = client.c
SERVER_SRCS = server.c

all: $(LIB_NAME) $(NAME) $(NAME_1)

$(LIB_NAME): 
	make -C $(LIB_PATH)

$(NAME): $(CLIENT_SRCS)
	gcc $(CFLAGS) $(CLIENT_SRCS) -L $(LIB_PATH) -lft -o $(NAME)

$(NAME_1): $(SERVER_SRCS)
	gcc $(CFLAGS) $(SERVER_SRCS) -L $(LIB_PATH) -lft -o $(NAME_1)

clean: 
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME) $(NAME_1)
	make -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re