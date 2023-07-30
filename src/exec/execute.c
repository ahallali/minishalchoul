/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:00:21 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/30 05:02:44 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var(t_std *var)
{
	var->old_stdrin = -1;
	var->old = dup(0);
	var->old_out = dup(1);
	var->stdrin = -1;
}

void	execute(t_minishell *g_minishell)
{
	int		fd[2];
	t_std	var;
	size_t	size;

	size = ft_lstsize(g_minishell->list_exec);
	init_var(&var);
	while (g_minishell->list_exec)
	{
		var.stdrout = -1;
		g_minishell->list = (t_exec_utils *)g_minishell->list_exec->content;
		printf("%s\n", g_minishell->list->cmd);
		if (!g_minishell->list->cmd)
		{
			g_minishell->last_exitstatus = 0;
			break ;
		}
		if (size == 1 && \
			is_builtin(g_minishell))
		{
			parent_builtin_red(g_minishell, var.old, var.old_out);
			break ;
		}
		if (g_minishell->list_exec->next)
			create_pipe(fd, &var.stdrout, &var.old_stdrin);
		create_fork(g_minishell, &var, fd);
		g_minishell->list_exec = g_minishell->list_exec->next;
	}
	close_fd(&var.old, &var.old_out);
	g_minishell->runned = 1;
}

void	create_fork(t_minishell *g_minishell, t_std *var, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("forkerror :");
		do_clean_exit(NULL, 2, 1, 1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close_fd(&var->old, &var->old_out);
		setup_child_process(g_minishell, &var->stdrin, &var->stdrout, fd);
	}
	else
		setup_parent_process(g_minishell, fd, &var->stdrin, &var->old_stdrin);
}

void	close_fd(int *old, int *old_out)
{
	close(*old);
	close(*old_out);
}

void	parent_builtin_red(t_minishell *g_minishell, int old, int old_out)
{
	if (g_minishell->list->input_fd != -1 || g_minishell->list->output_fd != -1)
	{
		if (g_minishell->list->input_fd != -1)
		{
			dup2(g_minishell->list->input_fd, 0);
			do_builtin(g_minishell);
			dup2(old, 0);
			close(g_minishell->list->input_fd);
		}
		if (g_minishell->list->output_fd != -1)
		{
			dup2(g_minishell->list->output_fd, 1);
			do_builtin(g_minishell);
			dup2(old_out, 1);
			close(g_minishell->list->output_fd);
		}
	}
	else
		do_builtin(g_minishell);
}
