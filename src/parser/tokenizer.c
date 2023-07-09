/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 03:30:54 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/10 00:06:58 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_info	*next_word(char *str, char *delimiter)
{
	t_token_info	*info;
	int				i;
	char			*c;

	if (!str)
		return (NULL);
	info = ft_calloc(1, sizeof(t_token_info));
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(QUOTES_PARSE, str[i]))
			skip_quoted(str, &i);
		if (str[i] && (ft_strchr(IO_PARSE, str[i]) != 0))
			return (token_io(str, &i, info));
		if (str[i] && ft_strchr(delimiter, str[i]))
			return (token_delim(str, &i, info));
		if (str[i])
			i++;
		if (!str[i])
			return (token_last(str, info));
	}
	return (NULL);
}

t_lex	*init_lexer_struct(void)
{
	t_lex	*lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		return (lex);
	lex->fd = -1;
	return (lex);
}

int	insert_to_lexer(char *str, t_parse_utils *u)
{
	t_list	*node;
	t_lex	*lex;
	t_lex	*last_lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (ft_strchr(IO_PARSE, *str))
		return (token_redirection (str, lex, last_lex, u));
	node = u->list_cmds;
	if (verify_exec_node(node, str, lex, u))
		return (1);
	node = ft_lstlast(u->list_cmds);
	last_lex = (t_lex *)node->content;
	if (*str == '|')
		return (insert_pipe(lex, u));
	else if (is_enum_redirection(last_lex->type)
		&& handle_lastlex_redir(last_lex, lex, str, u))
		return (1);
	else if (last_lex->type != PIPE && last_lex != lex)
		return (insert_args(lex, last_lex, str, u));
	else if (last_lex->type == PIPE
		|| (last_lex->type != ARG && last_lex->type != CMD))
		return (insert_command(lex, str, u, &node));
	return (0);
}
