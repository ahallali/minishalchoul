/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:09:31 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/04 00:48:19 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote_escaped(char *str, int i, char *flag)
{
	return ((str[i] == '\\' && str[i + 1] == *flag)
		|| (str[i] == '\\' && str[i + 1] == '$'
			&& *flag != '\''));
}

void	flag_quote(char c, char *flag)
{
	char	*final_flag;

	if (!flag)
		return ;
	final_flag = &g_minishell->quote_flag;
	if (flag)
		final_flag = flag;
	if (ft_strchr(QUOTES_PARSE, c) && !*final_flag)
		*final_flag = c;
	else if (*final_flag == c)
		*final_flag = 0;
}

char	*do_replace(char *str, char *var, int i)
{
	char	*res;

	if (path_finder(g_minishell->env, convert_path(var + 1)))
		res = ft_str_replace(str, var,
				path_finder(g_minishell->env, convert_path(var + 1)), i);
	else
	{
		if (ft_strequals(var + 1, "?"))
		{
			res = ft_str_replace(str, var, \
			ft_itoa(g_minishell->last_exitstatus), i);
		}
		else
			res = ft_str_replace(str, var, "", i);
	}
	return (res);
}
