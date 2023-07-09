/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/09 02:57:12 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redirection(t_minishell *minishell, int STDIN, int STDOUT)
{
    printf("===> %d\n", minishell->list->inputFd);
    if (minishell->list->inputFd > 2) // && !is_builtin(minishell))
        dup2(minishell->list->inputFd, 0);

    printf("===> %d\n", minishell->list->outputFd);
    if (minishell->list->outputFd > 2) // && !is_builtin(minishell))
        dup2(minishell->list->outputFd, 1);
}