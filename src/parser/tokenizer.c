/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/23 20:03:12 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ls -al | cat < Makefile | grep OBJ 2> errfile

#include "parser.h"

int	ft_str_contains(char *str, char c)
{
	while (str && *str && *str == c)
		return (1);
	return (0);
}

char* ft_strtok(char* str, const char* delimiters, char *skip) {
	static char		*token;
	static char		*lastToken;
	int				sFound;

	sFound = 0;
	if (str != NULL)
		token = str;
	else if (token == NULL)
		return (NULL);
	lastToken = token;
	if (*lastToken == '\0')
		return (NULL);
	while (*token != '\0')
	{
		if (ft_str_contains(skip, *token))
			sFound = 1;
		const char* delimiter = delimiters;
		while (*delimiter != '\0') 
		{
			if (*token == *delimiter) {
				*token = '\0';
				token++;
				return (lastToken);
			}
			delimiter++;
		}
		token++;
	}
	return (lastToken);
}

int parse_quote(char *prompt, t_parse_utils *p_prompt)
{
	char	*tmp;
	char	*cmd;
	t_lex	*lex;

	(void)p_prompt;
	tmp = ft_strtok(prompt, " ", NULL);
	lex = ft_calloc(1, sizeof(t_lex));
	while (tmp != NULL)
	{
		cmd = ft_strtrim(tmp, " ");
		tmp = ft_strtok(NULL, " ", NULL);
	}
	return (0);
}



// void parse_till_dquotes(char **word)
// {

// }



// int main()
// {
// }