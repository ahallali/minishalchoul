/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/21 22:35:24 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	// rl_catch_signals = 1;
void	handler(int sig)
{
	char	cr;

	(void)sig;
	cr = 13;
	// if (g_minishell->heredoc_flag)
	// 	signal(SIGINT, SIG_DFL);
	// printf("sig : %d", sig);
	if (g_minishell->heredoc_flag && sig == SIGINT)
	{
		g_minishell->sigint_flag = 1;
		write(STDIN_FILENO, &cr, 1);
	}
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	if (!g_minishell->heredoc_flag)
		rl_redisplay();
}

char	*get_home(t_minishell *g_minishell)
{
	t_node	*tmp;
	char	*t;

	t = NULL;
	tmp = g_minishell->env;
	while (tmp)
	{
		if (ft_strequals(tmp->variable, "HOME"))
			t = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (t);
}

	// if (signal == SIGINT)
	// {
	// }
	// 	minishell->sigint_flag = 1;
	// 	printf("ctrl c\n");
	// 	// if(minishell->heredoc_flag)
	// 	// write(stdrin_FILENO, "\n", 1);
	// 	// if (minishell->heredoc_flag)
	// 	// close(0);
	// else write(1, "\n", 1);