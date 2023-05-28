#ifndef MINISHELL_H
#define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft/libft.h"
# include "parser.h"
// void parse(char *line);
typedef struct s_node
{
    char *value;
    char *variable;
    void *next;
} t_node;
char *ft_strtok(char *str, const char *delimiters, char *skip) ;
// int ft_strlen(char *str);
void ft_env(char **env);
// char **ft_split(char *s, char c);
void echo(char **str);
// char *ft_substr(char *s, unsigned int start, size_t len);
void print_list(t_node *head);
void ft_pwd();
int ft_cd();
// void parse_prompt(char *p);


#endif
