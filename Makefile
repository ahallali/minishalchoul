# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 10:39:54 by ahallali          #+#    #+#              #
#    Updated: 2023/06/03 18:48:39 by ahallali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I /Users/ahallali/goinfre/.brew/opt/readline/include -fsanitize=address
LDFLAGS = -lreadline  
SRCS = minishell.c\
		bulltins.c\
		outils.c\
		env.c
OBJECTS = $(SRCS:.c=.o)
INCLUD = minishell.h

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c $(INCLUD)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L /Users/ahallali/goinfre/.brew/opt/readline/lib $(LDFLAGS)


clean:
	rm -rf $(OBJECTS)
	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)
	@echo "Cleaning objects and executable"

re: fclean all

