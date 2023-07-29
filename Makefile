NAME = minishell
CC = gcc
CFLAGS = -I /goinfre/ichaiq/.brew/opt/readline/include  -g 
LDFLAGS = -lreadline
SRCDIR = src
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
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -L /goinfre/ichaiq/.brew/opt/readline/lib $(LDFLAGS)

$(LIB):
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