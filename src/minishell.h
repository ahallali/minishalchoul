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
# include "../libft/libft.h"
// void parse(char *line);

# include "parser/parser.h"

typedef struct s_node
{
	char *value;
	char *variable;
	struct s_node *next;
}   t_node;

typedef struct s_exec_utils
{
    char    *cmd;
    t_list  *args;
    char    *infile;
    char    *outfile;
    int     inputFd;
    int     outputFd;
}           t_exec_utils;

typedef struct s_minishell
{
	t_node * env;
	t_exec_utils *list;
	struct s_list *list_exec;
} t_minishell;

t_minishell *minishell;


t_node *
ft_list_remove_if(t_node **head, char *data, int (*cmp)());
t_node *ft_env(char **env);
char *ft_strtok(char *str, const char *delimiters, char *skip) ;
void ft_echo(char **str,int fd);
// char *ft_substr(char *s, unsigned int start, size_t len);
void print_list(t_node *head);
void ft_pwd(t_node *head,char *s);
t_node * gt(char *str, t_node *head);
t_node *update_env(t_node *head, char *var, char *data);
void insert_node(t_node **head, char *value, char *variable);
char *path_finder(t_node *head, char *var);
t_node *ft_cd(t_minishell *head, char **t);
t_node *sort_var(t_node *head, char *s);
t_node *ft_export(t_node *head, char *s);
t_node *ft_unset(t_node *head, char *var);
// void parse_prompt(char *p);
void ft_exec(void *content);
int ft_check_n(char *str);
void update_path(char *str, char *cmd, char **agrs, char **env);
char **convert_env(t_node *node);
t_node *ft_empty(void);

char *expand_dquotes(char *str, t_minishell *u);

char **convert_command_args(t_exec_utils *utils);
#endif
