/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 01:29:27 by ichaiq            #+#    #+#             */
/*   Updated: 2023/05/28 10:16:36 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h" 

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
} lex_type;

typedef struct s_lex
{
    char *command_name;
    char *variable;
    char *filename;
    int  flag;
    int  fd;
    // void * hbnext;
    lex_type type;
} t_lex;


typedef struct s_token_info{
    char *word;
    char *limiter;
    char *next_start;
}               t_token_info;

typedef struct s_parse_utils
{
    t_lex   *lexer;
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
    int     inputFd;
    int     outputFd;
}           t_exec_utils;

void print_lex(void *lex);
void get_exec(t_parse_utils *u);

void parse_prompt(char *prompt ,t_parse_utils *utils);
int parse_quote(char *prompt, t_parse_utils *p_prompt);
int insert_to_lexer(char *str, t_parse_utils *u);