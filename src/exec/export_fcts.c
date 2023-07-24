/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_fcts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/24 01:54:30 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_key(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	check_key(char *str)
{
	int	i;
	int	bk;

	i = 1;
	bk = 0;
	if (isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && (str[i] != '=') && str[i] != '+')
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		if (str[i] == '\0' || str[i] == '=' || \
		(str[i] == '+' && str[i + 1] == '='))
			bk = 1;
	}
	if (bk == 1)
		return (0);
	return (1);
}

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
			return (i);
		i++;
	}
	return (0);
}

int	check_valid_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && !str[i + 1])
			return (i);
		i++;
	}
	return (0);
}

void	ft_export(char **args,t_minishell * g_minishell)
{
	int	x;

	x = 0;
	if (!args || !*args)
		print_export_list();
	while (args && args[x])
		add_value(args[x++],g_minishell);
	return ;
}
