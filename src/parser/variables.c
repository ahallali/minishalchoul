/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:52:17 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 16:23:34 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	is_valid_variable(char *var)
{
	int	i;

	i = 0;
	if (!var[i] || var[i] != '$' || !ft_isdigit(var[++i]))
		return (0);
	while (ft_isalpha(var[i]) || var[i] == 95 || ft_isdigit(var[i]))
		i++;
	if (!var[i])
		return (1);
	return (0);
}

char	*add_dollar_sign(char *var)
{
	int		len;
	char	*res;
	char	*tmp;

	len = ft_strlen(var) + 2;
	res = ft_calloc(len, sizeof(char));
	tmp = res;
	if (!tmp)
		return (tmp);
	*tmp++ = '$';
	while (var && *var)
		*tmp++ = *var++;
	return (res);
}

char	*extract_variable(char *str)
{
	int		i;

	i = 0;
	if (!str || !*str || *str != '$')
		return (NULL);
	if (ft_isdigit(str[++i]))
		return (ft_substr(str, 0, i + 1));
	if (str[i] == '?')
		return (ft_substr(str, 0, i + 1));
	while (!ft_strchr(" \t$\"\0", str[i])
		&& (ft_isalpha(str[i]) || str[i] == 95 || ft_isdigit(str[i])))
		i++;
	return (ft_substr(str, 0, i));
}
