/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:45:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/10 01:08:06 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
				quote = str[i];
			}
		}
		i++;
	}
	minishell->quote_flag = quote;
	return (quote);
}

char	*append_new_line(char *prompt, char delimiter)
{
	char		*tmp;
	char		*line;

	tmp = get_new_line(">", NULL, delimiter);
	line = ft_strjoin(prompt, "\n");
	free(prompt);
	prompt = ft_strjoin(line, tmp);
	return (free(line), free(tmp), prompt);
}

void	skip_quoted(char *str, int *i)
{
	minishell->quote_flag = str[*i];
	(*i)++;
	while (str[*i])
	{
		if (*i > 0 && str[*i] == minishell->quote_flag
			&& str[*i - 1] != '\\')
		{
			(*i)++;
			break ;
		}
		else
			(*i)++;
	}
}

int	is_enum_redirection(int val)
{
	return (val == REDIRECTION_AINPUT || val == REDIRECTION_INPUT
		|| val == REDIRECTION_AOUTPUT || val == REDIRECTION_OUTPUT);
}
