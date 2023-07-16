/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:10:06 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:11:20 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	parent(t_minishell *minishell, int *fd, int STDIN)
{
	if (minishell->list_exec->next)
		close(fd[1]);
	if (STDIN != -1)
		close(STDIN);
	if (minishell->list->inputFd > 2)
		close(minishell->list->inputFd);
	if (minishell->list->outputFd > 2)
		close(minishell->list->outputFd);
}

void	setup_parent_process(t_minishell *minishell, \
	int *fd, int *STDIN, int *old_stdin)
{
	parent(minishell, fd, *STDIN);
	if (minishell->list->inputFd > 2)
		close(minishell->list->inputFd);
	if (minishell->list->outputFd > 2)
		close(minishell->list->outputFd);
	*STDIN = *old_stdin;
}

void	wait_and_print_exit_status(void)
{
	int	status;
	int	exitstatus;

	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
		printf("%d", exitstatus);
	}
}
