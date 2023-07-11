/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/10 00:50:22 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
// void read_heredoc(int fd,)

void insert_heredoc(t_lex *lex, char *str)
{
    int fd[2];
    char *line;


    puts("test\n");
    if (pipe(fd)<0){
        perror("pipe error:");
        return ;
    }
    printf("word ! %s\n",minishell->token->word);
    if (minishell->token->next_start)
    {
        while (1)
        {
            line = readline(">");
            if (!ft_strncmp(minishell->token->word, line, ft_strlen(line)))
                break;
        }
        
    }
    else
    {
        while (1)
        {
            line = readline(">");
            if (!ft_strncmp(minishell->token->word, line, ft_strlen(line)))
                break;
            else
                ft_putstr_fd(line, fd[0]);
        }
    }

    lex->filename = str;
    lex->fd = fd[1];

    
}