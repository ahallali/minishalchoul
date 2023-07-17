/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 16:42:02 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*minishell;

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_parse_utils	*p_prompt;

	(void)ac;
	(void)av;
	line = NULL;
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (0);
	if (*env)
		minishell->env = ft_env(env, minishell);
	else
		minishell->env = ft_empty();
	fill_export_env(&minishell->env);
	minishell->last_exitstatus = 0;
	minishell->home = get_home(minishell);
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)handler);
		minishell->sigint_flag = 0;
		minishell->heredoc_flag = 0;
		line = readline("minishell>");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDIN_FILENO);
			exit(0);
		}
		p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		p_prompt->prompt = ft_strdup(line);
		minishell->list_exec = parse_prompt(p_prompt->prompt, p_prompt);
		if (!minishell->sigint_flag && minishell->list_exec)
			execute(minishell);
		free(line);
	}
}
