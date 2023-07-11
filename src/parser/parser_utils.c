/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/11 01:53:12 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*get_new_line(char *prompt, t_parse_utils *utils,char delimiter)

{
	(void)delimiter;
	char *tmp;

	(void)utils;
	tmp = readline(prompt);
	return (tmp);
}
/*
// if (!ft_strchr(tmp, c))
//     line = ft_strjoin(tmp, "\n"); 
// else
//     line = tmp;
*/

void	print_token(t_token_info *tok)
{
	if (tok->word)
		printf("tok word : %s\n", tok->word);
	if (tok->limiter)
		printf("tok lim : %s\n", tok->limiter);
	if (tok->next_start)
		printf("tok nxt : %s\n", tok->next_start);
	printf("--------------------\n");
}

t_list	*parse_prompt(char *prompt, t_parse_utils *utils)
{
	t_token_info	*tok;
	t_list			*result;

	while (validate_quote(prompt))
		prompt = append_new_line(prompt, minishell->quote_flag);
	tok = next_word(prompt, "| ");
	while (tok)
	{
		print_token(tok);
		minishell->token = tok;
		if (tok->word && !ft_strchr(" |",*tok->word))
			insert_to_lexer(tok->word, utils);
		// else if (tok->word && minishell->heredoc_flag)
		// 	insert_to_lexer(tok->word && minishell->heredoc_flag, utils);
		if (tok->limiter && tok->next_start && ((ft_strchr("|<>", *(tok->limiter)))))
			insert_to_lexer(tok->limiter, utils);
		else if (tok->limiter && ((ft_strchr("|<>", *(tok->limiter)))))
			insert_to_lexer(tok->limiter, utils);
		tok = next_word(tok->next_start, "|<> ");
	}
	ft_lstiter(utils->list_cmds, print_lex);
	result = get_exec(utils);
	return (result);
}

// ft_lstiter(utils->list_cmds, print_lex);
// printf("count : %d",ft_lstsize(res));
// ft_lstiter(res, print_exec);