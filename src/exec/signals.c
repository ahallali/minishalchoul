/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/09 23:50:22 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handler(int signal)
{
    (void)signal;
    if (waitpid(0, NULL, WNOHANG))
    {

        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else
        write(1, "\n", 1);
}