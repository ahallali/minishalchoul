/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:39:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/18 02:13:22 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_n(char *str)
{
	int	i;

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

int	check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*update_path(char *str, char *cmd)
{
	char	**tmp;
	char	*path;

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
