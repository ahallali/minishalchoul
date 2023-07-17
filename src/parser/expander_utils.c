/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:52:40 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 15:19:52 by ahallali         ###   ########.fr       */
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
	return ((ft_strlen(str) - (ft_strlen(find) * occ)
			+ (ft_strlen(replace) * occ)) + 1);
}

char	*ft_str_replace(char *str, char *find, char *replace, int start)
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
		if (!flag && i == (size_t) start
			&& ft_strncmp(&str[i], find, ft_strlen(find)) == 0)
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

int	has_valid_quoting(char *str)
{
	int		i;
	char	flag;
	int		valid;

	i = 0;
	valid = 0;
	while (str && str[i])
	{
		if (ft_strchr(QUOTES_PARSE, str[i]) && (!i
				|| (i && str[i - 1] != '\\')) && !flag)
			flag = str[i++];
		if (ft_strchr(&flag, str[i]) && (!i
				|| (i && str[i - 1] != '\\')) && flag)
		{
			flag = 0;
			valid = 1;
			i++;
			continue ;
		}
		i++;
	}
	return (valid);
}
