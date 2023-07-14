/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/13 22:45:32 by ahallali         ###   ########.fr       */
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
	
	// if (signal == SIGINT)
	// {
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
	// }
	// 	minishell->sigint_flag = 1;
	// 	printf("ctrl c\n");
	// 	// if(minishell->heredoc_flag)
	// 	// write(STDIN_FILENO, "\n", 1);
	// 	// if (minishell->heredoc_flag)
	// 	// close(0);
	// else write(1, "\n", 1);
}
