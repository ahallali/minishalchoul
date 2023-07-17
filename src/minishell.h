/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:16:31 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 18:55:08 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include <sys/types.h>
# define DELIMS_PARSE "|<>"
# define _DELIMS_PARSE "|<> \t"
# define IO_PARSE "<>"
# define QUOTES_PARSE "\"'"

typedef enum e_lex_type
{
	PIPE = 0,
	CMD = 1,
	ARG = 2,
	QUOTE = 3,
	DQUOTE = 4,
	REDIRECTION_INPUT = 5,
	REDIRECTION_OUTPUT = 6,
	REDIRECTION_AINPUT = 7,
	REDIRECTION_AOUTPUT = 8,
}	t_lex_type;

typedef struct s_lex
{
	char		*command_name;
	char		*variable;
	char		*filename;
	t_list		*infiles;
	int			flag_infile;
	t_list		*outfiles;
	int			flag_outfile;
	int			flag;
	int			fd;
	void		*next;
	t_lex_type	type;
}			t_lex;

typedef struct s_token_info
{
	char	*word;
	char	*limiter;
	char	*next_start;
}	t_token_info;

typedef struct s_parse_utils
{
	t_lex_type	*lexer;
	t_list		*list_cmds;
	t_list		*list_exec;
	int			wait_squote;
	int			wait_dquote;
	char		*prompt;
	char		*tmp_prompt;
}t_parse_utils;

typedef struct s_exec_utils
{
	char	*cmd;
	t_list	*args;
	char	*infile;
	char	*outfile;
	int		input_fd;
	int		output_fd;
	t_list	*infiles;
	int		flag_infile;
	t_list	*outfiles;
	int		flag_outfile;
}	t_exec_utils;
typedef struct s_node
{
	char			*value;
	char			*variable;
	struct s_node	*next;
}t_node;

typedef struct s_std
{
	int	stdrout;
	int	stdrin;
	int	old;
	int	old_out;
	int	old_stdrin;
}t_std;

typedef struct s_minishell
{
	t_node					*env;
	t_node					*export;
	t_exec_utils			*list;
	struct s_list			*list_exec;
	t_token_info			*token;
	char					quote_flag;
	char					*home;
	int						heredoc_flag;
	int						sigint_flag;
	int						last_exitstatus;
}	t_minishell;

t_minishell				*g_minishell;
t_exec_utils					*init_exec_utils(void);
void							close_last_fd(int fd);
char							*get_new_line(char *prompt,
									t_parse_utils *utils, char delimiter);
char							*append_new_line(char *prompt, char delimiter);
void							print_exec(void *exec);
void							print_lex(void *lex);
t_list							*parse_prompt(char *prompt, \
									t_parse_utils *utils);
int								insert_to_lexer(char *str, t_parse_utils *u);
void							parse_quotes(t_token_info *tok, \
									t_parse_utils *utils);
t_token_info					*next_word(char *str, char *delimiter);
t_list							*get_exec(t_parse_utils *u);
char							**convert_args(t_list *node);
char							**convert_command_args(t_exec_utils *utils);
int								validate_quote(char *str);
int								is_valid_variable(char *var);
char							*add_dollar_sign(char *var);
char							*extract_variable(char *str);
int								skip_quoted(char *str, int *i);
int								token_redirection(char *str, t_lex *lex, \
									t_lex *last_lex, t_parse_utils *u);
int								is_enum_redirection(int val);
int								open_file(char *filename, int flags);
void							convert_input_redirection(t_lex *tmp, \
									t_exec_utils *exec);
void							convert_output_redirection(t_lex *tmp, \
									t_exec_utils *exec);
int								handle_pipe(t_lex *tmp, t_list *l_tmp,
									t_exec_utils **exec, t_list **result);
int								get_output(t_lex *last_lex, char *str);
int								handle_lastlex_redir(t_lex *last_lex, \
									t_lex *lex,
									char *str, t_parse_utils *u);
int								verify_exec_node(t_list *node, char *str,
									t_lex *lex, t_parse_utils *u);
int								insert_pipe(t_lex *lex, t_parse_utils *u);
int								insert_args(t_lex *lex, t_lex *last_lex,
									char *str, t_parse_utils *u);
int								insert_command(t_lex *lex, char *str,
									t_parse_utils *u, t_list **node);
t_token_info					*token_io(char *str, int *i, \
									t_token_info *info);
t_token_info					*token_delim(char *str, int *i, \
									t_token_info *info);
t_token_info					*token_last(char *str, t_token_info *info);
int								get_heredoc_fd(char *limiter);
char							*expand_dquotes(char *str);
char							*remove_quote(char *str);
char							*ft_str_replace(char *str, char *find, \
										char *replace, int start);
char							*convert_path(char *str);
int								has_valid_quoting(char *str);
char							*expand_hdoc(char *str, int expand);
void							flag_quote(char c);
char							*do_replace(char *str, char *var, int i);
int								lex_analyze(t_parse_utils *utils);
t_node							*ft_list_remove_if(t_node **head, \
									char *data, int (*cmp)());
t_node							*ft_env(char **env, t_minishell *minishell);
char							*ft_strtok(char *str, \
									const char *delimiters, char *skip);
void							ft_echo(char **str, int fd);
void							print_list(t_node *head);
void							ft_pwd(t_node *head, char *s);
t_node							*movetodirectory(char *str, t_node *head);
void							tilda_and_movetodirectory(char **t, \
									t_minishell *head, char *tmp, t_node *new);
t_node							*update_env(t_node *head, \
									char *var, char *data);
void							insert_node(t_node **head, \
									char *value, char *variable);
char							*path_finder(t_node *head, char *var);
t_node							*ft_cd(t_minishell *head, char **t);
t_node							*sort_var(t_node *head, char *s);
void							ft_export(char **args);
t_node							*ft_unset(t_node **head, char *var);
void							execute(t_minishell *minishell);
void							ft_exec(void *content);
int								ft_check_n(char *str);
char							*update_path(char *str, char *cmd);
char							**convert_env(t_node *node);
void							child(t_minishell *minishell, int stdrin, \
									int stdrout, int *fd);
t_node							*ft_empty(void);
void							ft_sort_env(t_node **env);
void							open_pipes(t_minishell *minishell, \
									int *flag, int *tmp);
void							parent(t_minishell *minishell, \
									int *fd, int stdrin);
void							do_builtin(t_minishell *minishell);
int								is_builtin(t_minishell *minishell);
void							execute_cmd(t_minishell *minishell);
void							run_builltin(t_minishell *minishell);
void							redirection(t_minishell *minishell);
void							ft_exit(t_minishell *minishell, char **cmd);
int								check_cmd_num(char *cmd);
void							handler(int signal);
void							check_echo_arg(char **str, int fd);
int								check_key(char *str);
void							insert_to_export(char *key, \
									t_minishell *minishell);
int								check_value(char *str);
t_node							*add_to_export(t_node *head, \
									char *key, char *value);
void							add_value(char *arg);
void							print_export_list(void);
void							fill_keys(char **keys, t_node *head);
int								count_nodes(t_node *head);
t_node							*get_node(t_node *head, char *key);
void							sort_tab(char **arr, int n);
void							fill_export_env(t_node **head);
char							*get_home(t_minishell *minishell);
void							parent_builtin_red(t_minishell *minishell, \
										int old, int old_out);
void							create_pipe(int *fd, int *stdrout, \
										int *old_stdrin);
void							close_fd(int *old, int *old_out);
void							exit_status(void);
void							setup_parent_process(t_minishell *minishell, \
									int *fd, int *stdrin, int *old_stdrin);
void							wait_and_print_exit_status(void);
void							handle_builtin_redirection(t_minishell \
									*minishell, int old, int old_out);
void							setup_child_process(t_minishell *minishell, \
									int *stdrin, int *stdrout, int *fd);
void							create_fork(t_minishell *minishell, \
									t_std *var, int *fd);
void							init_var(t_std *var);
int								is_valid_key(char *var);
#endif
