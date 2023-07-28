/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:10:06 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/28 01:36:06 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent(t_minishell *g_minishell, int *fd, int stdrin)
{
	if (g_minishell->list_exec->next)
	{
		close(fd[1]);
	}
	if (stdrin != -1)
	{
		close(stdrin);
	}
	if (g_minishell->list->input_fd > 2)
	{
		close(g_minishell->list->input_fd);
	}
	if (g_minishell->list->output_fd > 2)
	{
		close(g_minishell->list->output_fd);
	}
}

void	setup_parent_process(t_minishell *g_minishell, \
	int *fd, int *stdrin, int *old_stdrin)
{
	parent(g_minishell, fd, *stdrin);
	if (g_minishell->list->input_fd > 2)
	{

		close(g_minishell->list->input_fd);
	}
	if (g_minishell->list->output_fd > 2)
	{

		close(g_minishell->list->output_fd);
	}
	*stdrin = *old_stdrin;
}

void	wait_and_print_exit_status(void)
{
	int	status;
	int	exitstatus;

	exitstatus = 0;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				ft_putstr_fd("\n", 1);
				g_minishell->last_exitstatus = 128 + WTERMSIG(status);
			}
			if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putstr_fd("Quit: 3\n", 1);
				g_minishell->last_exitstatus = 128 + WTERMSIG(status);
			}
		}
		else if (WIFEXITED(status))
		{
			exitstatus = WEXITSTATUS(status);
			g_minishell->last_exitstatus = exitstatus;
		}
	}
}
