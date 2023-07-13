/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/13 22:08:00 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	(void)sig;
	char cr;
	
	cr = 13;
	// rl_catch_signals = 1;
	if (minishell->heredoc_flag)
		signal(SIGINT, SIG_DFL);
	
	if (waitpid(0, NULL, WNOHANG))
	{
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
	else
		write(1, "\n", 1);
}
