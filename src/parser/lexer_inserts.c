/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inserts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:17:11 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/26 16:41:02 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_exec_node(t_list *node, char *str, t_lex *lex, t_parse_utils *u)
{
	if (!node && !ft_strchr(DELIMS_PARSE, *str))
	{
		lex->type = CMD;
		lex->command_name = str;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	return (0);
}

int	insert_pipe(t_lex *lex, t_parse_utils *u)
{
	lex->type = PIPE;
	ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
	return (1);
}

int	insert_args(t_lex *lex, t_lex *last_lex, char *str, t_parse_utils *u)
{
	lex->type = ARG;
	lex->variable = str;
	lex->command_name = last_lex->command_name;
	ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
	return (1);
}

int	insert_command(t_lex *lex, char *str,
		t_parse_utils *u, t_list **node)
{
	lex->type = CMD;
	lex->command_name = str;
	*node = ft_lstnew(lex);
	ft_lstadd_back(&u->list_cmds, *node);
	return (1);
}
