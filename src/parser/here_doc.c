/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/15 21:03:33 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_hdoc(char *str, int expand)
{
	int		i;
	char	*var;
	char	*res;
	char	*tmp;

	i = 0;
	res = str;
	while (res[i])
	{
		if (ft_strchr(QUOTES_PARSE, res[i]) && !minishell->quote_flag)
			minishell->quote_flag = res[i];
		else if (minishell->quote_flag == res[i])
			minishell->quote_flag = 0;
		if (res[i] == '$'
			&& !ft_strchr(" \t$\"\0", res[i + 1]) && res[i + 1] != '\0'
			&& expand)
		{
			tmp = ft_strdup(res);
			var = extract_variable(&tmp[i]);
			res = do_replace(res, var, i);
			continue ;
		}
		i++;
	}
	return (res);
}


int	get_heredoc_fd(char *limiter)
{
	int		fd[2];
	char	*line;
	int		expand;

	expand = !has_valid_quoting(limiter);
	limiter = remove_quote(limiter);
	if (pipe(fd) < 0)
		return (perror("pipe error:"), -1);
	minishell->heredoc_flag = 1;
	if (minishell->heredoc_flag)
		rl_catch_signals = 1;
	rl_getc_function = getc;
	while (1 && !minishell->sigint_flag)
	{
		line = readline("> ");
		if (ft_strequals(limiter, line) || !line)
			break ;
		ft_putstr_fd(ft_strjoin(expand_hdoc(line, expand), "\n"), fd[1]);
		free(line);
	}
	minishell->heredoc_flag = 0;
	rl_catch_signals = 0;
	close(fd[1]);
	return (fd[0]);
}

