/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nnrm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:57:58 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/31 17:13:16 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_cmd_err(char *str)
{
	int		i;
	int		j;
	char	*t;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ':')
		{
			j = i;
			break ;
		}
		i++;
	}
	t = ft_strjoin(ft_substr(str, 0, j + 1), \
	ft_strjoin(" ", expand_dquotes(g_minishell->list->cmd)));
	res = ft_strjoin(t, ft_substr(str, j, ft_strlen(str)));
	return (res);
}

int	check_cmd_num(char *cmd)
{
	int	i;

	i = 1;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[0] == '-' || cmd[0] == '+' || ft_isdigit(cmd[0]))
		{
			if (!check_numbers(&cmd[0]))
				return (0);
		}
		else
		{
			return (1);
			break ;
		}
		i++;
	}
	return (1);
}

int	check_numbers(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_cmd_num(char *cmd)
{
	int	i;

	i = 1;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[0] == '-' || cmd[0] == '+' || ft_isdigit(cmd[0]))
		{
			if (!check_numbers(&cmd[0]))
				return (0);
		}
		else
		{
			return (1);
			break ;
		}
		i++;
	}
	return (1);
}

char	*join_cmd_err(char *str)
{
	int		i;
	int		j;
	char	*t;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ':')
		{
			j = i;
			break ;
		}
		i++;
	}
	t = ft_strjoin(ft_substr(str, 0, j + 1),
			ft_strjoin(" ", expand_dquotes(g_minishell->list->cmd)));
	res = ft_strjoin(t, ft_substr(str, j, ft_strlen(str)));
	return (res);
}
