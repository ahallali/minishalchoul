/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:09:31 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/31 16:10:03 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			&& !ft_strchr(" \t$\"\0", res[i + 1]) && res[i + 1] != '\0'
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
