/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:45:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/08/04 23:13:59 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (ft_strchr(QUOTES_PARSE, str[i]))
		{
			if (quote == str[i]
				&& (i > 0 && str[i - 1] != '\\'))
			{
				quote = 0;
			}
			else if (!quote)
			{
				ft_putstr_fd("QUOTES ERROR\n",2);
				quote = str[i];
				break;
				return (256);
			}
		}
		i++;
	}
	g_minishell->quote_flag = quote;
	return (quote);
}

char	*append_new_line(char *prompt, char delimiter)
{
	char		*tmp;
	char		*line;
	char		*res;

	tmp = get_new_line("> ", NULL, delimiter);
	res = NULL;
	if (tmp)
		res = ft_strdup(tmp);
	line = ft_strjoin(prompt, "\n");
	if (res)
		return (free(tmp), ft_strjoin(line, res));
	else
	{
		write(STDOUT_FILENO, "\n", 1);
		return (free(tmp), res);
	}
	return (prompt);
}

int	skip_quoted(char *str, int *i)
{
	g_minishell->quote_flag = str[*i];
	(*i)++;
	while (str[*i])
	{
		if (*i > 0 && str[*i] == g_minishell->quote_flag
			&& str[*i - 1] != '\\')
		{
			(*i)++;
			g_minishell->quote_flag = 0;
			return (str[*i]);
		}
		else
			(*i)++;
	}
	return (0);
}

int	is_enum_redirection(int val)
{
	return (val == REDIRECTION_AINPUT || val == REDIRECTION_INPUT
		|| val == REDIRECTION_AOUTPUT || val == REDIRECTION_OUTPUT);
}
