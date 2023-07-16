/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:08:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:16:51 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int *fd, int *STDOUT, int *old_stdin)
{
	if (pipe(fd) < 0)
	{
		perror("pipe:");
		exit(1);
	}
	else
	{
		*STDOUT = fd[1];
		*old_stdin = fd[0];
	}
}

void	setup_child_process(t_minishell *minishell, \
	int *STDIN, int *STDOUT, int *fd)
{
	child(minishell, *STDIN, *STDOUT, fd);
	redirection(minishell);
	execute_cmd(minishell);
	ft_lstiter(*get_gcollector(), ft_free);
}

void	child(t_minishell *minishell, int STDIN, int STDOUT, int *fd)
{
	if (STDIN != -1)
	{
		dup2(STDIN, 0);
		close(STDIN);
	}
	if (STDOUT != -1)
	{
		dup2(STDOUT, 1);
		close(STDOUT);
	}
	if (minishell->list_exec->next)
		close(fd[0]);
}

void	redirection(t_minishell *minishell)
{
	if (minishell->list->inputFd > 2)
		dup2(minishell->list->inputFd, 0);
	if (minishell->list->outputFd > 2)
		dup2(minishell->list->outputFd, 1);
}

void	execute_cmd(t_minishell *minishell)
{
	char	*path;

	path = NULL;
	path = update_path(path_finder(minishell->env, "PATH") \
	, expand_dquotes(minishell->list->cmd));
	if (execve(path, convert_command_args(minishell->list), \
	convert_env(minishell->env)) == -1)
	{
		if (errno == EACCES)
		{
			perror("minishell");
			exit (126);
		}	
		exit(127);
	}
}
			// else if (errno == ENOENT) 
			//     ft_putstr_fd("minishell:Command not found\n", 2);
			// else if (errno == )
				// ft_putstr_fd("minishell:No such file or directory\n", 2);
