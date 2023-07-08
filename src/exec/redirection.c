/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/08 19:33:31 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"


void redirection (t_minishell * minishell ,int STDIN ,int STDOUT)
{
    if (minishell->list->inputFd > 2 && !is_builtin(minishell))
        dup2(minishell->list->inputFd, 0);
    if (minishell->list->outputFd > 2 && !is_builtin(minishell))
        dup2(minishell->list->outputFd,1);
}