/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:39:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/11 22:25:01 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_n(char *str)
{
	int i;

	i = 1;
	if (!str || !*str)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int check_cmd(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char *update_path(char *str, char *cmd)
{
	char **tmp;
	char *path;

	tmp = NULL;
	if (!str || !cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.' || check_cmd(cmd))
		return (cmd);
	tmp = ft_split(str, ':');
	while (tmp && *tmp)
	{
		if (!access(cmd, X_OK | F_OK))
			return (cmd);
		else
		{
			path = ft_strjoin(*tmp, ft_strjoin("/", cmd));
			if (!access(path, X_OK | F_OK))
				return (path);
			tmp++;
		}
	}
	return (NULL);
}

void execute_one(t_minishell *minishell, pid_t pid)
{
	char *path;

	path = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		path = update_path(path_finder(minishell->env,
									   "PATH"),
						   expand_dquotes(minishell->list->cmd));
		if (path)
		{
			if (execve(path, convert_command_args(minishell->list),
					   convert_env(minishell->env)) == -1)
				perror("execve");
		}
		ft_lstiter(*get_gcollector(), ft_free);
	}
}
