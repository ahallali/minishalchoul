/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 03:30:54 by ichaiq            #+#    #+#             */
/*   Updated: 2023/05/29 00:13:57 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_quote(char *prompt, t_parse_utils *p_prompt)
{
    char *tmp = ft_strtok(prompt," ",NULL);
    char *cmd;
    t_lex *lex;
    (void)p_prompt;
    lex = ft_calloc(1, sizeof(t_lex));
    while (tmp != NULL)
    {
        
        // printf("parser : %s\n",tmp );
        cmd = ft_strtrim(tmp, " ");
        
        
        tmp = ft_strtok(NULL," ",NULL);
    
    }
    return 0;
}

int insert_to_lexer(char *str, t_parse_utils *u)
{
    t_list *node;
    t_lex *lex;
    t_lex *last_lex;

    lex = ft_calloc(1, sizeof(t_lex));
    // t_list *last_node;
    
    // node = u->list_cmds;
    node = ft_lstlast(u->list_cmds);
    if (!node )
    {
        lex->type = CMD;
        lex->command_name = str;
        node = ft_lstnew(lex);
        ft_lstadd_back(&u->list_cmds, node);
        printf("CMD %s in lexer\n",str);
        return (1);
    }
    
    last_lex = (t_lex*)node->content;
    if (*str == '|')
    {
        lex->type = PIPE;
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        printf("PIPE in lexer\n");
        return (1);

    }
    else if (*str == '>' || (ft_strlen(str) == 2 && (str[1] == '>')))
    {
        ///     ***IMPORTANT***
        //   create a new fd in case there are multiple outfiles
        // ex: ls -al | grep .c < Makefile > outfiles >oj
        lex->type = REDIRECTION_OUTPUT;
        lex->command_name = last_lex->command_name;
        // printf("str is : %s\n",str);

        if ((ft_strlen(str) == 2 && (str[1] == '>')))
        {
            str[1] = '\0';
            lex->fd = ft_atoi(str);
        }
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        printf("REDIRECTION_OUTPUT %d in lexer\n",lex->fd);

        return (1);
        
    }
    else if (*str == '<' || (ft_strlen(str) == 2 && str[1] == '<'))
    { 
        ///     ***IMPORTANT***
        //   create a new fd in case there are multiple outfiles
        // ex: ls -al | grep .c < Makefile > outfiles >oj
        lex->type = REDIRECTION_INPUT;
        lex->command_name = last_lex->command_name;
        
        
        if ((ft_strlen(str) == 2 && (str[1] == '<' )))
        {
            str[1] = '\0';
            lex->fd = ft_atoi(str);

        }
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        printf("REDIRECTION_INPUT %d in lexer\n",lex->fd);
        return (1);

        
    }
    else if (last_lex->type == PIPE)
    {
        lex->type = CMD;
        lex->command_name = str;
        node = ft_lstnew(lex);
        ft_lstadd_back(&u->list_cmds, node);
        printf("CMD '%s' in lexer\n",str);
        return (1);
    }
    else if (last_lex->type == CMD || last_lex->type == ARG)
    {
        lex->type = ARG;
        // lex->last
        lex->variable = str;
        lex->command_name = last_lex->command_name;
        ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        printf("ARGS '%s' in lexer\n",str);
        return (1);

    }
    else if ((last_lex->type == REDIRECTION_OUTPUT || last_lex->type == REDIRECTION_INPUT )
         && !(last_lex->fd == -1 && !last_lex->filename))
    {

        last_lex->filename = str;
        lex->variable = str;
        // ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
        printf("modified REDIRECT OF %s TO '%s' in lexer\n", last_lex->command_name, str);
        return (1);

    }
    
    // if (last_lex->type == CMD)
    //     printf("last is cmd \n");
    return (0);
}