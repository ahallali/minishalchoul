/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/10 00:50:22 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection(t_minishell *minishell)
{
	if (minishell->list->inputFd > 2)
		dup2(minishell->list->inputFd, 0);
	if (minishell->list->outputFd > 2)
		dup2(minishell->list->outputFd, 1);
}
