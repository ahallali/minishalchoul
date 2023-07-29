/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:08:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/29 21:43:53 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int *fd, int *stdrout, int *old_stdrin)
{
	if (pipe(fd) < 0)
	{
		perror("pipe:");
		do_clean_exit(NULL, 2, 1, 1);
	}
	else
	{
		*stdrout = fd[1];
		*old_stdrin = fd[0];
	}
}

void	setup_child_process(t_minishell *g_minishell,
		int *stdrin, int *stdrout, int *fd)
{
	char *cmd;

	cmd = expand_dquotes(g_minishell->list->cmd);
	child(g_minishell, *stdrin, *stdrout, fd);
	redirection(g_minishell);
	if (!cmd)
		do_clean_exit(NULL, 2, 0, 1);
	execute_cmd(cmd, g_minishell);
}
	// ft_lstiter(*get_gcollector(), ft_free);

void	child(t_minishell *g_minishell, int stdrin, int stdrout, int *fd)
{
	if (stdrin != -1)
	{
		dup2(stdrin, 0);
		close(stdrin);
	}
	if (stdrout != -1)
	{
		dup2(stdrout, 1);
		close(stdrout);
	}
	if (g_minishell->list_exec->next)
	{
		close(fd[0]);
	}
}

void	redirection(t_minishell *g_minishell)
{
	if (g_minishell->list->input_fd > 2)
		dup2(g_minishell->list->input_fd, 0);
	if (g_minishell->list->output_fd > 2)
		dup2(g_minishell->list->output_fd, 1);
}

void	execute_cmd(char *cmd, t_minishell *g_minishell)
{
	char	*path;

	path = NULL;
	if (is_builtin(g_minishell))
	{
		do_builtin(g_minishell);
		exit(0);
	}
	path = update_path(path_finder(g_minishell->env, "PATH"),
			cmd);
	if (execve(path, convert_command_args(g_minishell->list),
			   convert_env(g_minishell->env)) == -1)
	{
		error_exec(path);
	}
	do_clean_exit(NULL, 2, 0, 1);
}
