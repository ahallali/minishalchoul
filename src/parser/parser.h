/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:29:27 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/23 19:47:32 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../minishell.h" 

#ifndef PARSER_H
#define PARSER_H

#define DELIMS_PARSE "|<>"
#define _DELIMS_PARSE "|<> 	"
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
	char		*command_name;
	char		*variable;
	char		*filename;
	int			flag;
	int			fd;
	void		*next;
	t_lex_type 	type;
} t_lex;


typedef struct s_token_info{
	char *word;
	char *limiter;
	char *next_start;
}               t_token_info;

typedef struct s_parse_utils
{
	t_lex_type		*lexer;
	t_list			*list_cmds;
	t_list			*list_exec;
	int				wait_squote;
	int				wait_dquote;
	char			*prompt;
	char			*tmp_prompt;
}				t_parse_utils;


t_token_info	*init_token_struct();
t_token_info	*validate_dquotes(char *str, int *i);


char			*ft_strtok(char *str, const char *delimiters, char *skip) ;
void			print_exec(void *exec);
void			print_lex(void *lex);
t_list			*parse_prompt(char *prompt, t_parse_utils *utils);
int				parse_quote(char *prompt, t_parse_utils *p_prompt);
int				insert_to_lexer(char *str, t_parse_utils *u);
void			parse_quotes(t_token_info *tok, t_parse_utils *utils);
t_token_info	*next_word(char *str, char *delimiter);
t_list			*get_exec(t_parse_utils *u);
char			**convert_args(t_list *node);
int				dquote_finder(char *str, int i);
char			*add_dollar_sign(char *var);
char			*extract_variable(char *str);

#endif