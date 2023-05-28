/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/05/28 04:46:44 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//ls -al | cat < Makefile | grep OBJ 2> errfile


#include "minishell.h"

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
    while (*token != '\0') {
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

t_token_info *next_word(char *str, char *delimiter)
{
    t_token_info *info;
    int i;
    int flag;
    char *c;

    flag = 0;
    if (!str)
        return (NULL);
    info = ft_calloc(1, sizeof(t_token_info));
    i = 0;
    while (str[i] != '\0')
    {
        c = ft_strchr(delimiter, str[i]);
        if (c)
        {
            info->word = ft_substr(str, 0, i);
            while (str[i + 1] == *c)
                i++;
            info->limiter = &str[i];
            info->next_start = &str[i +1 ];
            return info;
        }
        i++;
        if (!str[i])
        {
            info->word = str;
            info->limiter = NULL;
            info->next_start =NULL;
            return info;
        }
    }
    return NULL;
}

void parse_quotes(t_token_info *tok, t_parse_utils *utils)
{
    int i;
    char c;
    
    i = 1;
    if ((*tok->next_start == '"' || *tok->next_start == '\'') 
        && ft_strlen(tok->next_start) > 1)
    {
        c = *tok->next_start;
        while (tok->next_start[i] != c)
            i++; 
        if (tok->next_start[i] == c)
        {
            insert_to_lexer(ft_substr(tok->next_start, 0, ++i), utils);
            tok->next_start = &tok->next_start[i];
        }
        else 
            utils->wait_dquote = 1;
    }

}


void parse_prompt(char *prompt ,t_parse_utils *utils)
{

    t_token_info * tok = next_word(prompt, " |");
    while (tok)
    {

        // if (tok->word)
        // printf("tok word : %s\n", tok->word);
        // if (tok->limiter)
        // printf("tok lim : %c\n", *(tok->limiter));
        // if (tok->next_start)
        // printf("tok nxt : %s\n", tok->next_start);
        // printf("--------------------\n");
        if (!ft_strchr(" |",*tok->word))
            insert_to_lexer(tok->word, utils);
        if (tok->limiter && ( ft_strchr("|<>",*(tok->limiter))))
        {
            if (*(tok->limiter) )
            insert_to_lexer(tok->limiter, utils);
        }
        if (tok->next_start && (*tok->next_start == '"' || *tok->next_start == '\''))
            parse_quotes(tok, utils);
        tok = next_word(tok->next_start, " |<>");
    }
    

    // (void)p;
    // char *prompt = ft_strdup(p_prompt->prompt);
    
    // char *tmp = ft_strtok(prompt," ","");
    // char *cmd;
    // t_lex *lex;
    
    // lex = ft_calloc(1, sizeof(t_lex));
    // while (tmp != NULL)
    // {
        
    //     // printf("parser : %s\n",tmp );
    //     cmd = ft_strtrim(tmp, " ");
    //     insert_to_lexer(cmd, utils);
    //     // if (ft_strchr())
        
    //     tmp = ft_strtok(NULL," ","");
    
    // }
    // return 0;
    
    
    
    
}

// int main()
// {
// }