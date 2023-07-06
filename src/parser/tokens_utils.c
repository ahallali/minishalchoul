/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:09:42 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/06 13:42:52 by ichaiq           ###   ########.fr       */
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

int	t_redirect(char *str, t_lex *lex, t_lex *last_lex, t_parse_utils *u)
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

int get_redir_file(char *str, t_lex *lex, t_lex *last_lex, t_parse_utils *u)
{
	last_lex->filename = str;
	if (last_lex->type == REDIRECTION_OUTPUT && !last_lex->filename)
	{
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_outfile = O_CREAT | O_TRUNC | O_WRONLY;
		lex->variable = str;
		return (1);
	}
	else if (last_lex->type == REDIRECTION_INPUT  && !last_lex->filename)
	{
		ft_lstadd_back(&last_lex->infiles, ft_lstnew(str));
		last_lex->flag_infile = O_RDONLY;
		return (1);
	}
	else if (last_lex->type == REDIRECTION_AOUTPUT  && !last_lex->filename)
	{
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_infile = O_CREAT | O_APPEND | O_WRONLY;
		return (1);
	}
	// CHECK AINPUT
	return (0);
}

int is_redirection(enum e_lex_type type)
{
	if (type == REDIRECTION_AOUTPUT || type == REDIRECTION_OUTPUT
		|| type == REDIRECTION_AINPUT || type == REDIRECTION_INPUT)
		return (1);
	else
		return (0);
}

int is_token(char c)
{
	if (ft_strchr(DELIMS_PARSE, c))
		return (1);
	else
		return (0);
}