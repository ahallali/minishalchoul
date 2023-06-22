/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 03:30:54 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/22 18:32:02 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


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
        // c = ft_strchr(delimiter, str[i]);
        // if ((!i || str[i - 1] != '\\') 
        //     &&str[i] == '"' && !minishell->dquote_flag)
        // {
        //     puts("f addded \n");
        //     // printf(" : %c\n",str[i]);
        //     printf("str[i] : %c\n",str[i]);
        //     printf("str[i - 1] : %c\n",str[i - 1]);
        //     minishell->dquote_flag = '"';
        // }
        // else if ((i && str[i-1] != '\\') 
        //     && str[i] && str[i] == '"' && minishell->dquote_flag == '"')
        // {        
        //     printf("str[i] : %c\n",str[i]);
        //     printf("str[i - 1] : %c\n",str[i - 1]);
        //     minishell->dquote_flag = '\0';
        // }
        if (str[i] == '"')
        {
            // puts("test\n");
            if (minishell->dquote_flag != '"')
            {
                printf("f added \n");
                minishell->dquote_flag = '"';
            }
            if (minishell->dquote_flag == '"')
            {
                // printf("str[i - 1] : %c\n",str[i - 1]);
                while (str[i])
                {
                    // puts("while\n");
                    printf("str[%d] : %c\n", i, str[i]);
                    if (i > 0 && str[i] == '"' && str[i - 1] == '\\')
                        continue;
                    else if (str[i] == '"')
                    {
                        minishell->dquote_flag = '\0'; 
                        // printf("f ended \n");
                    }
                    i++;
                }
                
                if (!str[i])
                {
                    info->word = str;
                    info->limiter = NULL;
                    info->next_start = NULL;
                    return (info);
                }
                // if (i != 0 && str[i - 1] != '\\')
                // {
                //     minishell->dquote_flag = '\0'; 
                //     printf("f ended \n");
                //     i++;
                // }   
            }
        }
        // printf("dquote_flag : %d\n",minishell->dquote_flag);
        // printf("errorororr\n");        
        // REDIRECTIONS
        if (!minishell->dquote_flag && (c = ft_strchr(IO_PARSE, str[i]) ) != 0)
        {
            printf("test : %s\n", &str[i]);
            
            info->word = ft_substr(str, 0, i);
            if ((ft_strnchr(IO_PARSE, str[i + 1], 1) && ft_strnchr(IO_PARSE, str[i + 2], 1)
                )|| (str[i] == IO_PARSE[1] && str[i + 1] == IO_PARSE[0]))
                return (perror("Syntax error : unexpected token found1"),NULL);
            while (str[i + 1] == *c && !ft_strchr("<>",*c))
                i++;
            // printf("str[i] %c\n",str[i]);
            // printf("str[i + 1] %c\n",str[i + 1]);
            if (str[i] == str[i + 1])
                info->limiter = ft_substr(str, i, 2);
            else if (ft_isdigit(str[i-1]))
            {
                // while (ft_isdigit(str[--i]))
                //     ;
                
                info->limiter = ft_substr(str, i, 2);
                info->word = ft_substr(str + 1, 0, i);
            }
            else {
                info->limiter = &str[i];
                info->word = ft_substr(str, 0, i);
                // info->word = ft_substr(str, 0, i);
            }
            info->next_start = &str[i + 1];
            return (info);
        }
        // TOKEN DELIMITER
        // printf("strchr : %s\n", ft_strchr(delimiter, str[i]));
        // printf("delimiter : %s\n", delimiter);
        // printf("str : %s\n", &str[i]);
        if (minishell->dquote_flag == 0 && (c = ft_strchr(delimiter, str[i]) ))
        {
            // puts("delimiter found\n");
            info->word = ft_substr(str, 0, i);
            // if (str[i] == *delimiter && str[i + 1] == *delimiter)
            // printf("str[i] : %c\n",str[i]);
            // printf("str[i + 1] : %c\n",str[i + 1]);
            // printf("delimiter : %c\n",*delimiter);
            if (ft_strnchr(DELIMS_PARSE, str[i], 2) && 
                ft_strnchr(DELIMS_PARSE, str[i + 1],1))
                return (perror("Syntax error : unexpected token found2"),NULL);
            info->limiter = &str[i];
            info->next_start = &str[i + 1];
            return (info);
        }
        i++;
        if (!str[i] && !minishell->dquote_flag)
        {
            info->word = str;
            info->limiter = NULL;
            info->next_start = NULL;
            return (info);
        }
        // else {
        //     info->word = str;
        //     info->limiter = NULL;
        //     info->next_start = NULL;
        //     return (info);
        // }
        // if (ft_strStartWith(info->word, '"') && !ft_strEndsWith(info->word, '\''))
        // while (/* condition */)
        // {
        //     /* code */
        // }
        
    }
    return NULL;
}

int insert_to_lexer(char *str, t_parse_utils *u)
{
    t_list *node;
    t_lex *lex;
    t_lex *last_lex;

    lex = ft_calloc(1, sizeof(t_lex));
    // t_list *last_node;
    
    // node = u->list_cmds;
    // printf("str : %s\n",str);
    node = ft_lstlast(u->list_cmds);
    if (!str || !*str)
        return (0);
    if (!node )
    {
        lex->type = CMD;
        lex->command_name = str;
        node = ft_lstnew(lex);
        ft_lstadd_back(&u->list_cmds, node);
        return (1);
    }
    
    last_lex = (t_lex*)node->content;
    if (*str == '|')
    {
        lex->type = PIPE;
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        return (1);

    }
    else if ((*str == '>' || (ft_strlen(str) == 2 && (str[1] == '>')))
        && last_lex->type != REDIRECTION_OUTPUT)
    {
        ///     ***IMPORTANT***
        //   create a new fd in case there are multiple outfiles
        // ex: ls -al | grep .c < Makefile > outfiles >oj
        lex->type = REDIRECTION_OUTPUT;
        lex->command_name = last_lex->command_name;
        lex->flag = W_OK;
        // printf("str is : %s\n",str);

        if ((ft_strlen(str) == 2 && (str[1] == '>')))
        {
            str[1] = '\0';
            lex->fd = ft_atoi(str);
        }
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));

        return (1);
        
    }
    else if (*str == '<' || (ft_strlen(str) == 2 && str[1] == '<'))
    { 
        ///     ***IMPORTANT***
        //   create a new fd in case there are multiple outfiles
        // ex: ls -al | grep .c < Makefile > outfiles >oj
        lex->type = REDIRECTION_INPUT;
        lex->command_name = last_lex->command_name;
        lex->flag = R_OK;
        
        
        if ((ft_strlen(str) == 2 && (str[1] == '<' )))
        {
            str[1] = '\0';
            lex->fd = ft_atoi(str);

        }
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        return (1);

        
    }
    else if (last_lex->type == REDIRECTION_OUTPUT && !last_lex->filename)
    {

        last_lex->filename = str;
        lex->variable = str;
        // ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        return (1);
    }
    else if (last_lex->type == REDIRECTION_INPUT && !last_lex->filename)
    {

        last_lex->filename = str;
        lex->variable = str;
        // ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        return (1);
    }
    else if (last_lex->type != PIPE)
    {
        lex->type = ARG;
        // lex->last
        lex->variable = str;
        lex->command_name = last_lex->command_name;
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        return (1);

    }
    // else if (last_lex->type == CMD || last_lex->type == ARG)
    // {
    //     lex->type = ARG;
    //     // lex->last
    //     lex->variable = str;
    //     lex->command_name = last_lex->command_name;
    //     ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
    //     printf("ARGS '%s' in lexer\n",str);
    //     return (1);

    // }
    else if (last_lex->type == PIPE || last_lex->type != ARG)
    {
        lex->type = CMD;
        lex->command_name = str;
        node = ft_lstnew(lex);
        ft_lstadd_back(&u->list_cmds, node);
        return (1);
    }
    // else if (G)
    // {
        
    // }
    

    // else if ((last_lex->type == REDIRECTION_OUTPUT || last_lex->type == REDIRECTION_INPUT )
    //      && !(last_lex->fd == -1 && !last_lex->filename))
    // {

    //     last_lex->filename = str;
    //     lex->variable = str;
    //     // ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
    //     printf("modified REDIRECT OF %s TO '%s' in lexer\n", last_lex->command_name, str);
    //     return (1);
    // }
    
    // if (last_lex->type == CMD)
    //     printf("last is cmd \n");
    return (0);
}
t_list *parse_prompt(char *prompt ,t_parse_utils *utils)
{
    
    minishell->dquote_flag = 0;
    minishell->squote_flag = 0;
    t_token_info * tok = next_word(prompt, " |");
    while (tok)
    {

        if (tok->word)
            printf("tok word : %s\n", tok->word);
        if (tok->limiter)
            printf("tok lim : %s\n", tok->limiter);
        if (tok->next_start)
            printf("tok nxt : %s\n", tok->next_start);
        printf("--------------------\n");

        if (!ft_strchr(" |",*tok->word) && (tok->next_start != tok->word))
            insert_to_lexer(tok->word, utils);
        // puts("first nice \n");
        if (tok->limiter && ( (ft_strchr("|<>",*(tok->limiter)))))
            insert_to_lexer(tok->limiter, utils);
        // puts("second nice \n");

        if ((tok->next_start 
            && (ft_strchr(QUOTES_PARSE, *tok->next_start) || ft_strchr(QUOTES_PARSE, *tok->word)))
            || minishell->dquote_flag != 0)
            parse_quotes(tok, utils);
        // puts("third nice \n");
            
        tok = next_word(tok->next_start, "|<> ");
    }
    // ft_lstiter(utils->list_cmds, print_lex);
    // t_list *res = get_exec(utils);
    // printf("count : %d",ft_lstsize(res));
    // ft_lstiter(res, print_exec);
    return get_exec(utils);
    
}