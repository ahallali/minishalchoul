/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:38 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	// rl_catch_signals = 1;
void	handler(int sig)
{
	char	cr;

	(void)sig;
	cr = 13;
	if (minishell->heredoc_flag)
		signal(SIGINT, SIG_DFL);
	if (minishell->heredoc_flag)
	{
		minishell->sigint_flag = 1;
		write(STDIN_FILENO, &cr, 1);
	}
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	if (!minishell->heredoc_flag)
		rl_redisplay();
}

char	*get_home(t_minishell *minishell)
{
	t_node	*tmp;
	char	*t;

	t = NULL;
	tmp = minishell->env;
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
	// 	// write(STDIN_FILENO, "\n", 1);
	// 	// if (minishell->heredoc_flag)
	// 	// close(0);
	// else write(1, "\n", 1);