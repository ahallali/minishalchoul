# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahallali <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 10:39:54 by ahallali          #+#    #+#              #
#    Updated: 2023/06/04 19:16:53 by ahallali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I /Users/ahallali/goinfre/.brew/opt/readline/include -fsanitize=address
LDFLAGS = -lreadline  
SRCS = minishell.c\
		cd_builtin.c\
		outils.c\
		env.c
LIB = libft/libft.a
OBJECTS = $(SRCS:.c=.o)
INCLUD = minishell.h

.PHONY: all clean fclean re

all: $(NAME)

$(LIB):
	make bonus -C libft 
	make clean

%.o: %.c $(INCLUD) $(lib)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -L /Users/ichaiq/goinfre/.brew/opt/readline/lib $(LDFLAGS)


clean:
	rm -rf $(OBJECTS)
	make clean -C libft/

	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

	@echo "Cleaning objects and executable"

re: fclean all