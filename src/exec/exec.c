/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:39:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/24 19:07:03 by ahallali         ###   ########.fr       */
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
	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	if (!str || !cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.' || check_cmd(cmd))
		return (cmd);
	tmp = ft_split(str, ':');
	while (tmp && *tmp)
	{
		if (cmd && *cmd)
			path = ft_strjoin(*tmp, ft_strjoin("/", cmd));
		if (!access(path, X_OK & F_OK))
			return (path);
		tmp++;
	}
	return (NULL);
}
