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
# include <sys/wait.h>
# include<stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include "parser/parser.h"
#include <sys/types.h>

typedef struct s_node
{
	char *value;
	char *variable;
	struct s_node *next;
}   t_node;

typedef struct s_std
{
	int STDOUT;
	int STDIN;
	int old;
	int old_out;
	int old_stdin;
} t_std;

typedef struct s_minishell
{
	t_node			*env;
	t_node 			*export;
	t_exec_utils	*list;
	struct s_list	*list_exec;
	t_token_info	*token;
	char			quote_flag;
	char			*home;
	int heredoc_flag;
	int				sigint_flag;
	int				last_exitstatus;
}					t_minishell;

extern t_minishell *minishell;
void execute_one(t_minishell *minishell, pid_t pid);
t_node *ft_list_remove_if(t_node **head, char *data, int (*cmp)());
t_node *ft_env(char **env, t_minishell *minishell);
char *ft_strtok(char *str, const char *delimiters, char *skip) ;
void ft_echo(char **str,int fd);
void print_list(t_node *head);
void ft_pwd(t_node *head,char *s);
t_node *movetodirectory(char *str, t_node *head);
void tilda_and_movetodirectory(char **t, t_minishell *head, char *tmp, t_node *new);
t_node *update_env(t_node *head, char *var, char *data);
void insert_node(t_node **head, char *value, char *variable);
char *path_finder(t_node *head, char *var);
t_node *ft_cd(t_minishell *head, char **t);
t_node *sort_var(t_node *head, char *s);
void ft_export(char **args);
t_node *ft_unset(t_node **head, char *var);
void execute(t_minishell *minishell);
void ft_exec(void *content);
int ft_check_n(char *str);
char *update_path(char *str, char *cmd);
char **convert_env(t_node *node);
void child(t_minishell *minishell, int STDIN, int STDOUT ,int *fd);
t_node *ft_empty(void);
void ft_sort_env(t_node **env);
void open_pipes(t_minishell *minishell,int* flag ,int *tmp);
void parent(t_minishell *minishell, int *fd, int STDIN);
void do_builtin(t_minishell *minishell);
int is_builtin(t_minishell *minishell);
void execute_cmd(t_minishell *minishell);
void run_builltin(t_minishell *minishell);
void redirection(t_minishell *minishell);
void ft_exit(t_minishell *minishell, char **cmd);
int check_cmd_num(char *cmd);
void handler(int signal);
void check_echo_arg(char **str, int fd);
int check_key(char *str);
void insert_to_export(char *key, t_minishell *minishell);
int check_value(char *str);
t_node *add_to_export(t_node *head, char *key, char *value);
void	add_value(char *arg);
void 	print_export_list();
void fill_keys(char **keys, t_node *head);
int count_nodes(t_node *head);
t_node *get_node(t_node *head, char *key);
void sort_tab(char** arr, int n);
void fill_export_env(t_node **head);
char *get_home(t_minishell *minishell);
void parent_builtin_red(t_minishell *minishell,int old,int old_out);
void	create_pipe(int *fd, int *STDOUT, int *old_stdin);
void	close_fd(int *old, int *old_out);
void	exit_status();
void	setup_parent_process(t_minishell *minishell, int *fd, int *STDIN,int *old_stdin);
void	wait_and_print_exit_status();
void	handle_builtin_redirection(t_minishell *minishell, int old, int old_out);
void	setup_child_process(t_minishell *minishell, int *STDIN, int *STDOUT, int *fd);
void	create_fork( t_minishell *minishell,t_std *var,int *fd);
void	init_var(t_std *var);
int		is_valid_key(char *var);
#endif
