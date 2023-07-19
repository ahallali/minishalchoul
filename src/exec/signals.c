/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/19 02:25:47 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	// rl_catch_signals = 1;
void	handler(int sig)
{
	char	cr;

	(void)sig;
	cr = 13;
	if (g_minishell->heredoc_flag)
		signal(SIGINT, SIG_DFL);
	if (g_minishell->heredoc_flag)
	{
		g_minishell->sigint_flag = 1;
		write(STDIN_FILENO, &cr, 1);
	}
	write(1, "\n", 1);
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
		if (!ft_strncmp(tmp->variable, "HOME", 5))
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