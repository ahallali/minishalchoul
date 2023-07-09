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
#include <sys/wait.h>
# include<stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include "parser/parser.h"
#include <sys/types.h>
// void parse(char *line);


typedef struct s_node
{
	char *value;
	char *variable;
	struct s_node *next;
}   t_node;

typedef struct s_minishell
{
	t_node			*env;
	t_exec_utils	*list;
	struct s_list	*list_exec;
	char			quote_flag;
}					t_minishell;

t_minishell *minishell;
void execute_one(t_minishell *minishell, pid_t pid);
t_node *ft_list_remove_if(t_node **head, char *data, int (*cmp)());
t_node *ft_env(char **env);
char *ft_strtok(char *str, const char *delimiters, char *skip) ;
void ft_echo(char **str,int fd);
void print_list(t_node *head);
void ft_pwd(t_node *head,char *s);
t_node * gt(char *str, t_node *head);
t_node *update_env(t_node *head, char *var, char *data);
void insert_node(t_node **head, char *value, char *variable);
char *path_finder(t_node *head, char *var);
t_node *ft_cd(t_minishell *head, char **t);
t_node *sort_var(t_node *head, char *s);
void ft_export(t_node **env, char **args);
t_node *ft_unset(t_node *head, char *var);
void execute(t_minishell *minishell);
void ft_exec(void *content);
int ft_check_n(char *str);
char *update_path(char *str, char *cmd);
char **convert_env(t_node *node);
void child(t_minishell *minishell, int STDIN, int STDOUT ,int *fd);
t_node *ft_empty(void);
void ft_sort_env(t_node **env);
void open_pipes(t_minishell *minishell,int* flag ,int *tmp);
void parent(t_minishell *minishell, int *fd, int STDIN,int old_stdin);
void do_builtin(t_minishell *minishell);
int is_builtin(t_minishell *minishell);
void execute_cmd(t_minishell *minishell, char *path);
void run_builltin(t_minishell *minishell);
// void redirection(t_minishell *minishell);
void redirection(t_minishell *minishell, int STDIN, int STDOUT);
void ft_exit(t_minishell *minishell, char *cmd);
int check_cmd_num(char *cmd);
#endif
