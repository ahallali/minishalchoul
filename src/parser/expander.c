/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 15:19:19 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*remove_quote(char *str)
{
	int		i;
	int		y;
	char	*result;
	char	flag;

	flag = 0;
	i = 0;
	y = 0;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str && str[i])
	{
		if (ft_strchr(QUOTES_PARSE, str[i]) && (!i
				|| (i && str[i - 1] != '\\')) && !flag)
			flag = str[i++];
		if (ft_strchr(&flag, str[i]) && (!i
				|| (i && str[i - 1] != '\\')) && flag)
		{
			flag = 0;
			i++;
			continue ;
		}
		result[y++] = str[i++];
	}
	return (result);
}

void	flag_quote(char c)
{
	if (ft_strchr(QUOTES_PARSE, c) && !minishell->quote_flag)
		minishell->quote_flag = c;
	else if (minishell->quote_flag == c)
		minishell->quote_flag = 0;
}

char	*do_replace(char *str, char *var, int i)
{
	char	*res;

	if (path_finder(minishell->env, convert_path(var + 1)))
		res = ft_str_replace(str, var,
				path_finder(minishell->env, convert_path(var + 1)), i);
	else
	{
		if (ft_strequals(var + 1, "?"))
			res = ft_str_replace(str, var, \
			ft_itoa(minishell->last_exitstatus), i);
		else
			res = ft_str_replace(str, var, "", i);
	}
	return (res);
}

char	*expand_dquotes(char *str)
{
	int		i;
	char	*var;
	char	*res;
	char	*tmp;

	i = 0;
	res = str;
	while (res && res[i])
	{
		flag_quote(res[i]);
		if (res[i] == '$'
			&& !ft_strchr(" \t$\"\0", res[i + 1]) && res[i + 1] != '\0'
			&& minishell->quote_flag != '\'')
		{
			tmp = ft_strdup(res);
			var = extract_variable(&tmp[i]);
			res = do_replace(res, var, i);
			continue ;
		}
		i++;
	}
	return (remove_quote(res));
}
