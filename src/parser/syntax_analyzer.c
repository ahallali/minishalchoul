/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:03:19 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 16:23:34 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	lex_analyze(t_parse_utils *utils)
{
	t_list	*n;
	t_lex	*lex;

	n = utils->list_cmds;
	if (validate_quote(utils->prompt))
		return (ft_putstr_fd("unexpected EOF while looking \
for matching `\"'\n", STDERR_FILENO), 0);
	while (n)
	{
		lex = (t_lex *)n->content;
		if (is_enum_redirection(lex->type) && !lex->filename)
			return (ft_putstr_fd("Syntax error: unexpcted token \
after redirection\n", STDERR_FILENO), 0);
		else if (lex->type == PIPE && !n->next)
			return (ft_putstr_fd("Syntax error: expected token \
after pipe\n", STDERR_FILENO), 0);
		n = n->next;
	}
	return (1);
}
