/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/08 16:32:58 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_occ(char *str, char *find)
{
	int	i;
	int	count;

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

int	result_len(char *str, char *find, char *replace)
{
	int	occ;

	occ = 1;
	return ((ft_strlen(str)
			- (ft_strlen(find) * occ) + (ft_strlen(replace) * occ)) + 1);
}

char	*ft_str_replace(char *str, char *find, char *replace)
{
	size_t	i;
	size_t	y;
	int		flag;
	char	*result;

	i = 0;
	y = 0;
	flag = 0;
	result = ft_calloc(result_len(str, find, replace) + 1, sizeof(char));
	while (str[i])
	{
		if (!flag && ft_strncmp(&str[i], find, ft_strlen(find)) == 0 && !flag)
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

char	*convert_path(char *str)
{
	int	i;

	i = 0;
	if (i == 0 && str[i] == '$')
		i++;
	return (ft_strdup(&str[i]));
}

char	*expand_dquotes(char *str, t_minishell *u)
{
	int		i;
	char	*var;
	char	*res;
	char	*tmp;

	i = 0;
	res = str;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_strdup(str);
			var = extract_variable(&tmp[i]);
			printf("var : %s\n", var);
			if (path_finder(u->env, convert_path(var + 1)))
				res = ft_str_replace(res, var,
						path_finder(minishell->env, convert_path(var + 1)));
			else
				res = ft_str_replace(res, var, "");
		}
		i++;
	}
	printf("original str : %s\n", str);
	printf("result : %s\n", res);
	return (res);
}
