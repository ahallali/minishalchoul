/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/12 23:35:07 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handler(int signal)
{
	
	if (signal == SIGINT)
	{
		puts("test");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
		// readline("minishell>");
	}
	// 	minishell->sigint_flag = 1;
	// 	printf("ctrl c\n");
	// 	// if(minishell->heredoc_flag)
	// 	// write(STDIN_FILENO, "\n", 1);
	// 	// if (minishell->heredoc_flag)
	// 	// close(0);
	// else write(1, "\n", 1);
}
