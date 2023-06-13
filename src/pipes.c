/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:59:44 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/13 13:01:44 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void open_pipes(t_minishell *minishell, int *flag, int *tmp)
{
    if (!minishell->list_exec)
        return;
        
        if (minishell->list_exec->next)
        {  
            if (minishell->list_exec->next && *flag ==0)
            {
                close(tmp [0]);
                dup2(minishell->list->inputFd,STDIN_FILENO);
                dup2(tmp[1], 1);
                close(tmp [1]);
                *flag = 1;
            }
            else if(minishell->list_exec->next)
            {
                close(tmp[0]);
                dup2(tmp[1], 1);
                close(tmp[1]);
                dup2(minishell->fd_out, 0);
                printf("pipe reading : %d\n", tmp[0]);
                printf("pipe writing : %d\n", tmp[1]);
            }
            else if (pipe(tmp))
                    perror("pipeerror");
            }
        else 
        {
            printf("here1\n");
            close(tmp[1]);
            close(tmp [0]);
            dup2(minishell->fd_out, 0);
            minishell->list->inputFd = tmp[0];
             minishell->list->outputFd = STDOUT_FILENO;
        }
        if (*flag != 0)
             close(minishell->fd_out);
}
