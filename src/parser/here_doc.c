/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/11 02:04:10 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



// void read_heredoc(int fd,)

int get_heredoc_fd(char *limiter)
{
    int fd[2];
    char *line;

    puts("test\n");
    if (pipe(fd)<0)
    {
        perror("pipe error:");
        return (-1);
    }
    while (1)
    {
        line = readline(">");
        if (!ft_strncmp(limiter, line, ft_strlen(line)))
            break;
        else
            ft_putstr_fd(ft_strjoin(line, "\n"), fd[1]);
    }
    close(fd[1]);
    return (fd[0]);
}

