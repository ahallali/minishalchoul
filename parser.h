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
    PIPE,
    QUOTE,
    CMD,
    ARG,
    // FILE,
    REDIRECTION_INPUT,    
    REDIRECTION_OUTPUT,    
} lex_type;

typedef struct s_lex
{
    char *command_name;
    char *variable;
    char *filename;
    int  fd;
    void *next;
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
    int     wait_squote;
    int     wait_dquote;
    char    *prompt;
    char    *tmp_prompt;
} t_parse_utils;

void parse_prompt(char *prompt ,t_parse_utils *utils);
int parse_quote(char *prompt, t_parse_utils *p_prompt);
int insert_to_lexer(char *str, t_parse_utils *u);