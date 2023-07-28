/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/28 01:23:04 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*g_minishell;

// void f()
// {
// 	system("leaks minishell");
// }

void	fill_export_minishell(t_minishell *g_minishell)
{
	fill_export_env(&g_minishell->env);
	g_minishell->last_exitstatus = 0;
	g_minishell->home = get_home(g_minishell);
}

int	allocation_and_env(char **env)
{
	g_minishell = ft_calloc(1, sizeof(t_minishell));
	if (!g_minishell)
		return (0);
	if (*env)
		g_minishell->env = ft_env(env, g_minishell);
	else
		g_minishell->env = ft_empty();
	return (1);
}

void	signals_and_line(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)handler);
	g_minishell->sigint_flag = 0;
	g_minishell->heredoc_flag = 0;
}

int	prompt_and_exec(t_parse_utils *p_prompt, char *line)
{
	p_prompt = ft_calloc(1, sizeof(t_parse_utils));
	if (!p_prompt)
		return (1);
	p_prompt->prompt = ft_strdup(line);
	g_minishell->list_exec = parse_prompt(p_prompt->prompt, p_prompt);
	if (!g_minishell->sigint_flag && g_minishell->list_exec)
	{
		g_minishell->runned = 1;
		execute(g_minishell);
		wait_and_print_exit_status();
	}
	g_minishell->runned = 0;
	return (0);
}

	// atexit(f);
int	main(int ac, char **av, char **env)
{
	char			*line;
	t_parse_utils	*p_prompt;

	(void)ac;
	(void)av;
	alo = open("alo.txt", O_CREAT | O_APPEND | O_RDWR, 0644);
	p_prompt = NULL;
	line = NULL;
	allocation_and_env(env);
	fill_export_minishell(g_minishell);
	signals_and_line();
	while (1)
	{
		line = readline("minishell>");
		g_minishell->sigint_flag = 0;
		if (!line)
		{
			ft_putstr_fd("exit\n", STDIN_FILENO);
			free(line);
			do_clean_exit(NULL, 1, 0, 1);
		}
		prompt_and_exec(p_prompt, line);
		free(line);
	}
}
