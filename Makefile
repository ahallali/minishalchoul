# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 10:39:54 by ahallali          #+#    #+#              #
#    Updated: 2023/06/05 00:31:12 by ichaiq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -I /Users/ichaiq/goinfre/.brew/opt/readline/include  -fsanitize=address

LDFLAGS = -lreadline  
LIB = libft/libft.a
SRCS = minishell.c\
		bulltins.c\
		parser_utils.c\
		outils.c\
		env.c\
		parser_utils2.c\
		parser_utils3.c
OBJECTS = $(SRCS:.c=.o)
INCLUD = minishell.h

.PHONY: all clean fclean re

all: $(NAME)

$(LIB):
	make bonus -C libft 
	# make clean

%.o: %.c $(INCLUD) 
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

