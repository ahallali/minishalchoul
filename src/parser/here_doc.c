/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:07:48 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/24 19:00:10 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (ft_strchr(QUOTES_PARSE, res[i]) && !g_minishell->quote_flag)
			g_minishell->quote_flag = res[i];
		else if (g_minishell->quote_flag == res[i])
			g_minishell->quote_flag = 0;
		if (res[i] == '$' && !ft_strchr(" \t$\"\0", res[i + 1])
			&& res[i + 1] != '\0' && expand)
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

int	create_hd_file(char *name)
{
	(void)name;
	return (0);
}

int	io_heredoc(char *limiter, int expand, int fd)
{
	char	*line;

	line = readline("> ");
	if (ft_strequals(limiter, line) || !line)
		return (free(line), 1);
	ft_putstr_fd(ft_strjoin(expand_hdoc(line, expand), "\n"), fd);
	return (free(line), 0);
}

int	get_heredoc_fd(char *limiter)
{
	int		fd[2];
	int		expand;

	expand = !has_valid_quoting(limiter);
	limiter = remove_quote(limiter);
	if (pipe(fd) < 0)
		return (perror("pipe error:"), -1);
	g_minishell->heredoc_flag = 1;
	if (g_minishell->heredoc_flag)
		rl_catch_signals = 1;
	rl_getc_function = getc;
	while (1 && !g_minishell->sigint_flag)
	{
		if (io_heredoc(limiter, expand, fd[1]))
			break ;
	}
	g_minishell->heredoc_flag = 0;
	rl_catch_signals = 0;
	close(fd[1]);
	return (fd[0]);
}
