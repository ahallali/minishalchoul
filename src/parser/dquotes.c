/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:45:46 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/27 23:35:42 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

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
	printf("line : %s\n--", line);
	free(prompt);
	prompt = ft_strjoin(line, tmp);
	return (free(line), free(tmp), prompt);
}