/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 16:01:55 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include "parser.h"

char	*get_new_line(char *prompt, t_parse_utils *utils, char delimiter)

{
	char	*tmp;

	(void)delimiter;
	(void)utils;
	rl_catch_signals = 1;
	rl_getc_function = getc;
	minishell->heredoc_flag = 1;
	tmp = readline(prompt);
	minishell->heredoc_flag = 0;
	rl_catch_signals = 0;
	return (tmp);
}

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

	while (validate_quote(prompt) && !minishell->sigint_flag)
		prompt = append_new_line(prompt, minishell->quote_flag);
	if (!minishell->sigint_flag || (prompt && *prompt))
		add_history(prompt);
	utils->prompt = prompt;
	tok = next_word(prompt, "| \t");
	while (tok)
	{
		if (tok->word && !ft_strchr(" |\t", *tok->word))
			insert_to_lexer(tok->word, utils);
		if (tok->limiter && tok->next_start
			&& ((ft_strchr("|<>", *(tok->limiter)))))
			insert_to_lexer(tok->limiter, utils);
		else if (tok->limiter && ((ft_strchr("|<>", *(tok->limiter)))))
			insert_to_lexer(tok->limiter, utils);
		tok = next_word(tok->next_start, "|<> ");
	}
	if (!lex_analyze(utils))
		return (NULL);
	result = get_exec(utils);
	return (result);
}
