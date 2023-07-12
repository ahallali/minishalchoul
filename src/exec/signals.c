/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/12 02:48:10 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int signal)
{
	(void)signal;
	
	if (waitpid(0, NULL, WNOHANG))
	{
		minishell->sigint_flag = 1;
		printf("ctrl c\n");
		write(1, "\n", 1);
		// if(minishell->heredoc_flag)
			// write(STDIN_FILENO, "\n", 1);
		// if (minishell->heredoc_flag)
		rl_replace_line("", 1);
		// close(0);
		rl_on_new_line();
		rl_redisplay();

	}
	else
		write(1, "\n", 1);
}
