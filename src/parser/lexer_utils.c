/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:44:10 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/10 00:13:39 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_output(t_lex *last_lex,char *str)
{
	if (last_lex->type == REDIRECTION_OUTPUT && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_outfile = O_CREAT | O_TRUNC | O_WRONLY;
		return (1);
	}
	else if (last_lex->type == REDIRECTION_AOUTPUT && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_outfile = O_CREAT | O_APPEND | O_WRONLY;
		return (1);
	}
	return (0);
}

int	handle_lastlex_redir(t_lex *last_lex, t_lex *lex,
			char *str, t_parse_utils *u)
{
	if ((last_lex->type == REDIRECTION_OUTPUT
			|| last_lex->type == REDIRECTION_AOUTPUT)
		&& !last_lex->filename)
		return (get_output(last_lex, str));
	else if (last_lex->type == REDIRECTION_INPUT && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->infiles, ft_lstnew(str));
		last_lex->flag_infile = O_RDONLY;
		return (1);
	}
	else if (last_lex->type == REDIRECTION_AINPUT)
		insert_heredoc(last_lex, str);
	else if (is_enum_redirection(last_lex->type)
		&& last_lex->command_name == NULL)
	{
		lex->type = CMD;
		lex->command_name = str;
		last_lex->command_name = str;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	return (0);
}
