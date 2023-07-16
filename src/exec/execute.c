/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:00:21 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:41:25 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var(t_std *var)
{
	var->old_stdin = -1;
	var->old = dup(0);
	var->old_out = dup(1);
	var->STDIN = -1;
}

void	execute(t_minishell *minishell)
{
	int		fd[2];
	t_std	var;

	init_var(&var);
	while (minishell->list_exec)
	{
		var.STDOUT = -1;
		minishell->list = (t_exec_utils *)minishell->list_exec->content;
		if (!minishell->list->cmd)
			break ;
		if (is_builtin(minishell) && ft_lstsize(minishell->list_exec) == 1 \
			&& minishell->list->input_fd)
		{
			parent_builtin_red(minishell, var.old, var.old_out);
			break ;
		}
		if (minishell->list_exec->next)
			create_pipe (fd, &var.STDOUT, &var.old_stdin);
		create_fork(minishell, &var, fd);
		minishell->list_exec = minishell->list_exec->next;
	}
	close_fd(&var.old, &var.old_out);
	wait_and_print_exit_status();
}

void	create_fork( t_minishell *minishell, t_std *var, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("forkerror :");
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close_fd(&var->old, &var->old_out);
		setup_child_process(minishell, &var->STDIN, &var->STDOUT, fd);
	}
	else
		setup_parent_process(minishell, fd, &var->STDIN, &var->old_stdin);
}

void	close_fd(int *old, int *old_out)
{
	close(*old);
	close(*old_out);
}

void	parent_builtin_red(t_minishell *minishell, int old, int old_out)
{
	if (minishell->list->input_fd != -1 || minishell->list->output_fd != -1)
	{
		if (minishell->list->input_fd != -1)
		{
			dup2(minishell->list->input_fd, 0);
			do_builtin(minishell);
			dup2(old, 0);
			close(minishell->list->input_fd);
		}
		if (minishell->list->output_fd != -1)
		{
			dup2(minishell->list->output_fd, 1);
			do_builtin(minishell);
			dup2(old_out, 1);
			close(minishell->list->output_fd);
		}
	}
	else
		do_builtin(minishell);
}
