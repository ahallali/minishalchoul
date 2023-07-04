/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:29:27 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/28 02:00:50 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h" 


#ifndef PARSER_H
#define PARSER_H

#define DELIMS_PARSE "|<>"
#define _DELIMS_PARSE "|<> \t"
#define IO_PARSE "<>"
#define QUOTES_PARSE "\"'"

typedef enum e_lex_type
{
	PIPE = 0,
	CMD = 1,
	ARG = 2,
	QUOTE=3,
	DQUOTE=4,
	// FILE,
	REDIRECTION_INPUT=5,    
	REDIRECTION_OUTPUT=6,    
} t_lex_type;

typedef struct s_lex
{
	char *command_name;
	char *variable;
	char *filename;
	t_list *infiles;
	int		flag_infile;
	t_list *outfiles;
	int		flag_outfile;
	int  flag;
	int  fd;
	void *next;
	t_lex_type type;
} t_lex;


typedef struct s_token_info{
	char *word;
	char *limiter;
	char *next_start;
}               t_token_info;

typedef struct s_parse_utils
{
	t_lex_type   *lexer;
	t_list  *list_cmds;
	t_list  *list_exec;
	int     wait_squote;
	int     wait_dquote;
	char    *prompt;
	char    *tmp_prompt;
} t_parse_utils;


typedef struct s_exec_utils
{
	char    *cmd;
	t_list  *args;
	char    *infile;
	char    *outfile;
	int     inputFd;
	int     outputFd;
	t_list	*infiles;
	int		flag_infile;
	t_list	*outfiles;
	int		flag_outfile;
}           t_exec_utils;

char			*get_new_line(char *prompt,t_parse_utils *utils, char c);

char			*append_new_line(char *prompt, char delimiter);

void			print_exec(void *exec);
void			print_lex(void *lex);
t_list          *parse_prompt(char *prompt, t_parse_utils *utils);
int				parse_quote(char *prompt, t_parse_utils *p_prompt);
int				insert_to_lexer(char *str, t_parse_utils *u);
void			parse_quotes(t_token_info *tok, t_parse_utils *utils);
t_token_info	*next_word(char *str, char *delimiter);
t_list			*get_exec(t_parse_utils *u);
char			**convert_args(t_list *node);
char			**convert_command_args(t_exec_utils *utils);
int				validate_quote(char *str);
int				is_valid_variable(char *var);
char			*add_dollar_sign(char *var);
char			*extract_variable(char *str);


#endif