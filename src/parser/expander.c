/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/31 17:40:57 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote_escaped(char *str, int i, char *flag)
{
	return (str[i] == '\\' && str[i + 1] == *flag
		|| (str[i] == '\\' && str[i + 1] == '$'
			&& *flag != '\''));
}

char	*remove_quote(char *str)
{
	int		i;
	int		y;
	char	*result;
	char	*flag;

	flag = ft_calloc(2, sizeof(char));
	i = 0;
	y = 0;
	if (!ft_strlen(str))
		return (NULL);
	else if (ft_strlen(str) == 1 && *str == '~' && g_minishell->home)
		return (ft_strdup(g_minishell->home));
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str && str[i])
	{
		if (flag_setter_quotes(flag, str, &i) == 1)
			continue ;
		if (is_quote_escaped(str, i, flag))
			i++;
		result[y++] = str[i++];
	}
	return (result);
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

char	*expand_export(char *str)
{
	int		i;
	char	*res;
	char	flag;

	i = 0;
	flag = 0;
	res = str;
	while (res && res[i])
	{
		flag_quote(res[i], &flag);
		if (flag == '\'' && res[i] == '$'
			&& (i && res[i - 1] != '\\'))
		{
			res = ft_str_replace(res, "$", "\\$", i);
			i += 2;
			continue ;
		}
		i++;
	}
	return (expand_dquotes(res));
}
