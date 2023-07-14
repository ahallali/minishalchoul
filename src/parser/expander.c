/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/13 02:06:32 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int count_occ(char *str, char *find)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(find, &str[i], ft_strlen(find)))
		{
			count++;
			i += ft_strlen(find);
		}
		else
			i++;
	}
	return (count);
}

int result_len(char *str, char *find, char *replace)
{
	int occ;

	occ = 1;
	return ((ft_strlen(str) - (ft_strlen(find) * occ) + (ft_strlen(replace) * occ)) + 1);
}

char *ft_str_replace(char *str, char *find, char *replace, int start)
{
	size_t i;
	size_t y;
	int flag;
	char *result;

	i = 0;
	y = 0;
	flag = 0;
	result = ft_calloc(result_len(str, find, replace) + 1, sizeof(char));
	// printf("repl %d : %s\n", start, find);
	while (str[i])
	{
		// printf("fl :	%d	si :	%c	i :	%zu\n", flag, str[i], i);
		if (!flag && i == (size_t) start && ft_strncmp(&str[i], find, ft_strlen(find)) == 0)
		{
			i = i + ft_strlen(find);
			while (replace && (*replace != '\0'))
				result[y++] = *replace++;
			flag = 1;
		}
		else
			result[y++] = str[i++];
	}
	return (result);
}

char *convert_path(char *str)
{
	int i;

	i = 0;
	if (i == 0 && str[i] == '$')
		i++;
	return (ft_strdup(&str[i]));
}

char *remove_quote(char *str)
{
	int i;
	int y;
	int len;
	char *result;
	char flag;

	len = ft_strlen(str);
	flag = 0;
	i = 0;
	y = 0;
	result = ft_calloc(len + 1, sizeof(char));
	while (str[i])
	{
		if (ft_strchr(QUOTES_PARSE, str[i]) && (!i || (i && str[i - 1] != '\\')) && !flag)
			flag = str[i++];
		if (ft_strchr(&flag, str[i]) && (!i || (i && str[i - 1] != '\\')) && flag)
		{
			flag = 0;
			i++;
			continue;
		}
		result[y++] = str[i++];
	}
	return (result);
}

char *expand_dquotes(char *str)
{
	int i;
	char *var;
	char *res;
	char *tmp;

	i = 0;
	res = str;
	while (res[i])
	{
		if (ft_strchr(QUOTES_PARSE, res[i]) && !minishell->quote_flag )
			minishell->quote_flag = res[i];
		else if (minishell->quote_flag == res[i])
			minishell->quote_flag = 0;
		if (res[i] == '$' &&
			!ft_strchr(" \t$\"\0", res[i + 1]) && res[i + 1] != '\0'
			&& minishell->quote_flag != '\'')
		{
			tmp = ft_strdup(res);
			var = extract_variable(&tmp[i]);
			printf("var : %s\n", var);
			if (path_finder(minishell->env, convert_path(var + 1)))
				res = ft_str_replace(res, var,
									 path_finder(minishell->env, convert_path(var + 1)), i);
			else
				res = ft_str_replace(res, var, "", i);
			continue;
		}
		i++;
	}
	return (remove_quote(res));
}
