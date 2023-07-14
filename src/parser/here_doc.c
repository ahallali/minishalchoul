/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/13 22:44:23 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void read_heredoc(int fd,)

// void insert_heredoc(t_lex *lex, char *str)
// {
//     int fd[2];
//     char *line;

int get_heredoc_fd(char *limiter)
{
    int fd[2];
    char *line;

    // puts("test\n");
    if (pipe(fd) < 0)
        return (perror("pipe error:"), -1);
    minishell->heredoc_flag = 1;
    if (minishell->heredoc_flag)
		rl_catch_signals = 1;
    rl_getc_function = getc;
    while (1 && !minishell->sigint_flag)
    {
        // puts("tet");

        line = readline("> ");
        // printf("line %p : %s", line, line);
        if (ft_strequals(limiter, line) || !line)
            break;
        ft_putstr_fd(ft_strjoin(line, "\n"), fd[1]);
        free(line);
    }
    minishell->heredoc_flag = 0;
    rl_catch_signals = 0;

    close(fd[1]);
    return (fd[0]);
}

//     puts("test\n");
//     if (pipe(fd)<0){
//         perror("pipe error:");
//         return ;
//     }
//     printf("word ! %s\n",minishell->token->word);
//     if (minishell->token->next_start)
//     {
//         while (1)
//         {
//             line = readline(">");
//             if (!ft_strncmp(minishell->token->word, line, ft_strlen(line)))
//                 break;
//         }

//     }
//     else
//     {
//         while (1)
//         {
//             line = readline(">");
//             if (!ft_strncmp(minishell->token->word, line, ft_strlen(line)))
//                 break;
//             else
//                 ft_putstr_fd(line, fd[0]);
//         }
//     }

//     lex->filename = str;
//     lex->fd = fd[1];

// }
