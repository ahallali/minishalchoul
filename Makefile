# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 00:42:34 by ichaiq            #+#    #+#              #
#    Updated: 2023/08/08 00:18:34 by ahallali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I/Users/ahallali/goinfre/.brew/opt/readline/include -Wall -Wextra -Werror
SRCDIR = src
LDFLAGS = -lreadline
OBJDIR = obj
SRCS = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCLUD = src/minishell.h 
LIB = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUD)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -L/Users/ahallali/goinfre/.brew/opt/readline/lib $(LDFLAGS)

$(LIB): libft/*.c libft/*.h
	make bonus -C libft

clean:
	rm -rf $(OBJDIR)
	make clean -C libft/

	@echo "Cleaning objects"

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

	@echo "Cleaning objects and executable"

re: fclean all

.PRECIOUS: $(OBJECTS)