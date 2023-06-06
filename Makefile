# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 10:39:54 by ahallali          #+#    #+#              #
#    Updated: 2023/06/06 01:20:27 by ichaiq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I /Users/ahallali/goinfre/.brew/opt/readline/include -fsanitize=address
LDFLAGS = -lreadline  
SRCS = minishell.c\
		bulltins.c\
		cd_builtin.c\
		parser_utils.c\
		outils.c\
		env.c\
		parser_utils2.c\
		parser_utils3.c
OBJECTS = $(SRCS:.c=.o)
INCLUD = minishell.h
LIB=libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(LIB):
	make bonus -C libft 
	# make clean

%.o: %.c $(INCLUD) 
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -L /Users/ichaiq/goinfre/.brew/opt/readline/lib $(LDFLAGS)

$(LIB):
	make bonus -C libft 

clean:
	rm -rf $(OBJECTS)
	make clean -C libft/

	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

	@echo "Cleaning objects and executable"

re: fclean all