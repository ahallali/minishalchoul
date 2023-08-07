/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/07 22:19:20 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*expand_dquotes(char *str)
{
	int		i;
	char	*var;
	char	*res;
	char	*tmp;

	if (!str || !*str)
		return (NULL);
	i = 0;
	res = str;
	while (res && res[i])
	{
		flag_quote(res[i], &g_minishell->quote_flag);
		if (res[i] == '$'
			&& !ft_strchr(" \t\"\0", res[i + 1]) && res[i + 1] != '\0'
			&& (g_minishell->quote_flag != '\''
				&& (!(i && res[i - 1] == '\\'))))
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
