/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:09:42 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 15:16:29 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	token_redirection(char *str, t_lex *lex, t_lex *last_lex, t_parse_utils *u)
{
	if (!last_lex)
		last_lex = lex;
	lex->command_name = last_lex->command_name;
	if ((*str == '>' || (ft_strlen(str) == 2 && (str[1] == '>'))))
	{
		lex->type = REDIRECTION_OUTPUT;
		if ((ft_strlen(str) == 2 && (str[0] == str[1])))
			lex->type = REDIRECTION_AOUTPUT;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	else if (*str == '<' || (ft_strlen(str) == 2 && str[1] == '<'))
	{
		lex->type = REDIRECTION_INPUT;
		if ((ft_strlen(str) == 2 && (str[0] == str[1])))
		{
			lex->type = REDIRECTION_AINPUT;
			minishell->heredoc_flag = 1;
		}
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	return (0);
}

t_token_info	*token_io(char *str, int *i, t_token_info *info)
{
	char	*c;

	c = ft_strchr(IO_PARSE, str[*i]);
	info->word = ft_substr(str, 0, *i);
	if ((ft_strnchr(IO_PARSE, str[*i + 1], 1)
			&& ft_strnchr(IO_PARSE, str[*i + 2], 1))
		|| (str[*i] == IO_PARSE[1] && str[*i + 1] == IO_PARSE[0]))
		return (perror("Syntax error : unexpected token found"), NULL);
	while (str[*i + 1] == *c && !ft_strchr("<>", *c))
		(*i)++;
	if (str[*i] == str[*i + 1])
		info->limiter = ft_substr(str, (*i)++, 2);
	else
	{
		info->limiter = &str[*i];
		info->word = ft_substr(str, 0, *i);
	}
	info->next_start = &str[*i + 1];
	return (info);
}

t_token_info	*token_delim(char *str, int *i, t_token_info *info)
{
	info->word = ft_substr(str, 0, *i);
	if (ft_strnchr(DELIMS_PARSE, str[*i], 2)
		&& ft_strnchr(DELIMS_PARSE, str[*i + 1], 1))
		return (perror("Syntax error : unexpected token found2"), NULL);
	info->limiter = &str[*i];
	info->next_start = &str[*i + 1];
	return (info);
}

t_token_info	*token_last(char *str, t_token_info *info)
{
	info->word = str;
	info->limiter = NULL;
	info->next_start = NULL;
	return (info);
}
