/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/23 16:49:11 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//ls -al | cat < Makefile | grep OBJ 2> errfile


#include "parser.h"

int ft_str_contains(char *str, char c)
{
    while (str && *str && *str == c)
        return 1;
    return 0;
}

char* ft_strtok(char* str, const char* delimiters, char *skip) {
    static char* token;  
    static char* lastToken;
    int sFound;

    sFound = 0;
    if (str != NULL)
        token = str;
    else if (token == NULL)
        return NULL;

    lastToken = token;

    if (*lastToken == '\0')  
        return NULL;
    while (*token != '\0') 
    {
        if (ft_str_contains(skip, *token))
            sFound = 1;
        const char* delimiter = delimiters;
        while (*delimiter != '\0') {
            if (*token == *delimiter ) {
                *token = '\0';  
                token++;
                return lastToken;
            }
            delimiter++;
        }
        token++;
    }
    return lastToken;
}

int parse_quote(char *prompt, t_parse_utils *p_prompt)
{
    char *tmp = ft_strtok(prompt, " ", NULL);
    char *cmd;
    t_lex *lex;
    (void)p_prompt;
    lex = ft_calloc(1, sizeof(t_lex));
    while (tmp != NULL)
    {
        cmd = ft_strtrim(tmp, " ");
        tmp = ft_strtok(NULL, " ", NULL);
    }
    return 0;
}

char *get_new_line(char *prompt,t_parse_utils *utils, char c)
{
    char *line;
    char *tmp;

    (void)utils;
    tmp = readline(prompt);
    // if (!tmp)
    //     return (tmp);
    if (!ft_strchr(tmp, c))
    {
        line = ft_strjoin(tmp, "\n"); 
        free(tmp);
    }
    else
        line = tmp;
    return (line);   
}

void parse_quotes(t_token_info *tok, t_parse_utils *utils)
{
    int i;
    char c;
    char *line;
    
    i = 1;
    while ((*tok->next_start == '"' || *tok->next_start == '\'') 
        && ft_strlen(tok->next_start) >= 1)
    {
        c = *tok->next_start;
        while (tok->next_start[i] && tok->next_start[i] != c)
            i++; 
        if (tok->next_start[i] && tok->next_start[i] == c)
        {
            insert_to_lexer(ft_substr(tok->next_start, 0, ++i), utils);
            tok->next_start = &tok->next_start[i];
            break;
        }
        else {
            if (!utils->wait_dquote)
                tok->next_start =ft_strjoin(tok->next_start, "\n");
            utils->wait_dquote = 1;
            line = get_new_line(">", utils, c);
            tok->next_start = ft_strjoin(tok->next_start, line);
        }
    }

}

// void parse_till_dquotes(char **word)
// {

// }



// int main()
// {
// }