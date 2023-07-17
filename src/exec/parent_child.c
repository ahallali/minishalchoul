/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:10:06 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 17:00:27 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	parent(t_minishell *minishell, int *fd, int stdrin)
{
	if (minishell->list_exec->next)
		close(fd[1]);
	if (stdrin != -1)
		close(stdrin);
	if (minishell->list->input_fd > 2)
		close(minishell->list->input_fd);
	if (minishell->list->output_fd > 2)
		close(minishell->list->output_fd);
}

void	setup_parent_process(t_minishell *minishell, \
	int *fd, int *stdrin, int *old_stdrin)
{
	parent(minishell, fd, *stdrin);
	if (minishell->list->input_fd > 2)
		close(minishell->list->input_fd);
	if (minishell->list->output_fd > 2)
		close(minishell->list->output_fd);
	*stdrin = *old_stdrin;
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
		g_minishell->last_exitstatus = exitstatus;
	}
}
