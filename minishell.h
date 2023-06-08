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
	struct s_node *next;
}   t_node;

typedef struct s_minishell
{
	t_node * env;
	t_exec_utils *list;
	struct s_list *list_exec;
} t_minishell;

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
#endif
