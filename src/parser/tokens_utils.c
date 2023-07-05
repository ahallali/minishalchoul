/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:09:42 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/05 19:45:21 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
			break;
		}
		else (*i)++;
	}
}

int		token_redirection(char *str, t_lex *lex, t_lex *last_lex, t_parse_utils *u)
{
	if ((*str == '>' || (ft_strlen(str) == 2 && (str[1] == '>')))
	)
	{
		lex->type = REDIRECTION_OUTPUT;
		if ((ft_strlen(str) == 2 && (str[0] == str[1])))
			lex->type = REDIRECTION_AOUTPUT;
		lex->command_name = last_lex->command_name;
		// lex->flag = O_WRONLY;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	else if (*str == '<' || (ft_strlen(str) == 2 && str[1] == '<'))
	{ 
		lex->type = REDIRECTION_INPUT;
		if ((ft_strlen(str) == 2 && (str[0] == str[1])))
		{
			lex->type = REDIRECTION_AINPUT;
		}
		// lex->flag = O_RDONLY;
		lex->command_name = last_lex->command_name;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	return (0);
}