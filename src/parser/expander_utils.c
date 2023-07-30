/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:52:40 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/30 05:47:51 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!result)
		return (NULL);
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

int	flag_setter_quotes(char *flag, char *str, int *i)
{
	if (!*flag && is_flag_valid(QUOTES_PARSE, str, *i))
		*flag = str[(*i)++];
	if (*flag && is_flag_valid(flag, str, *i))
	{
		*flag = 0;
		i++;
		return (1);
	}
	return (0);
}
