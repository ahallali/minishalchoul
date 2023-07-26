/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/26 15:37:08 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"
#include"../minishell.h"

char	*get_new_line(char *prompt, t_parse_utils *utils, char delimiter)

{
	char	*tmp;

	(void)delimiter;
	(void)utils;
	rl_catch_signals = 1;
	rl_getc_function = getc;
	g_minishell->heredoc_flag = 1;
	tmp = readline(prompt);
	if (!tmp)
		signal(SIGINT, SIG_ERR);
	g_minishell->heredoc_flag = 0;
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

void	inserter_to_lexer(t_token_info *tok, t_parse_utils *utils)
{
	if (tok->word && !ft_strchr(" |\t", *tok->word))
		insert_to_lexer(tok->word, utils);
	if (tok->limiter && tok->next_start
		&& ((ft_strchr("|<>", *(tok->limiter)))))
		insert_to_lexer(tok->limiter, utils);
	else if (tok->limiter && ((ft_strchr("|<>", *(tok->limiter)))))
		insert_to_lexer(tok->limiter, utils);
}

t_list	*parse_prompt(char *prompt, t_parse_utils *utils)
{
	t_token_info	*tok;
	t_list			*result;
	char			*n_prompt;

	while ((validate_quote(prompt) && !g_minishell->sigint_flag))
	{
		n_prompt = append_new_line(prompt, g_minishell->quote_flag);
		if (!n_prompt)
			break ;
		prompt = n_prompt;
	}
	if (!g_minishell->sigint_flag || (prompt && *prompt))
		add_history(prompt);
	utils->prompt = prompt;
	tok = next_word(prompt, "| \t");
	if(!tok)
		return(NULL);
	while (tok)
	{
		inserter_to_lexer(tok, utils);
		tok = next_word(tok->next_start, "|<> ");
	}
	if (!lex_analyze(utils))
		return (NULL);
	result = get_exec(utils);
	return (result);
}
//