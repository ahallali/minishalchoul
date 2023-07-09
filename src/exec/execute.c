/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:00:21 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/09 15:28:34 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute(t_minishell *minishell)
{
	pid_t pid;
	int fd[2];
	int STDIN = -1;
	int old = dup(0);
	int old_out = dup(1);
	int STDOUT;
	int old_stdin = -1;
	char *path = NULL;

	while (minishell->list_exec)
	{
		STDOUT = -1;
		minishell->list = (t_exec_utils *)minishell->list_exec->content;
		if (!minishell->list->cmd)
			break;

		if (is_builtin(minishell) && ft_lstsize(minishell->list_exec) == 1 && minishell->list->inputFd)
		{
			if (minishell->list->inputFd != -1 || minishell->list->outputFd != -1)
			{
				if (minishell->list->inputFd != -1)
				{
					dup2(minishell->list->inputFd, 0);
					do_builtin(minishell);
					dup2(old, 0);
					close(minishell->list->inputFd);
				}
				if (minishell->list->outputFd != -1)
				{
					dup2(minishell->list->outputFd, 1);
					do_builtin(minishell);
					dup2(old_out, 1);
					close(minishell->list->outputFd);
				}
			}
			else
				do_builtin(minishell);
			break;
		}
		if (minishell->list_exec->next) 
		{
			
			if (pipe(fd) < 0)
			{
				perror("pipe:");
				exit(1);
			}
			else
			{
				STDOUT = fd[1];
				old_stdin = fd[0];
			}
		}
		pid = fork();
		if (pid < 0)
		{
			perror("forkerror :");
			exit(1);
		}
		if (pid == 0)
		{
			close(old);
			close(old_out);
			child(minishell, STDIN, STDOUT, fd);
			redirection(minishell, STDIN, STDOUT);
			execute_cmd(minishell, path);
			ft_lstiter(*get_gcollector(), ft_free);
		}
		else
		{
			parent(minishell, fd, STDIN, old_stdin);
			if (minishell->list->inputFd > 2)
				close(minishell->list->inputFd);
			if (minishell->list->outputFd > 2)
				close(minishell->list->outputFd);
			STDIN = old_stdin;
		}
		minishell->list_exec = minishell->list_exec->next;
	}
	close(old);
	close(old_out);
	while (waitpid(-1, NULL, 0) != -1)
		;
}
void child(t_minishell *minishell, int STDIN, int STDOUT, int *fd)
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
void parent(t_minishell *minishell, int *fd, int STDIN, int old_stdin)
{
	if (minishell->list_exec->next)
		close(fd[1]);
	if (STDIN != -1)
		close(STDIN);
}
void execute_cmd(t_minishell *minishell, char *path)
{
	path = update_path(path_finder(minishell->env, "PATH"), minishell->list->cmd);
	if (!path)
		perror("path not found");
	else
	{
		if (execve(path, convert_command_args(minishell->list), convert_env(minishell->env)) == -1)
			perror("execve");
	}
}
