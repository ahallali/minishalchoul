/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:10:06 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:42:13 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	parent(t_minishell *minishell, int *fd, int STDIN)
{
	if (minishell->list_exec->next)
		close(fd[1]);
	if (STDIN != -1)
		close(STDIN);
	if (minishell->list->input_fd > 2)
		close(minishell->list->input_fd);
	if (minishell->list->output_fd > 2)
		close(minishell->list->output_fd);
}

void	setup_parent_process(t_minishell *minishell, \
	int *fd, int *STDIN, int *old_stdin)
{
	parent(minishell, fd, *STDIN);
	if (minishell->list->input_fd > 2)
		close(minishell->list->input_fd);
	if (minishell->list->output_fd > 2)
		close(minishell->list->output_fd);
	*STDIN = *old_stdin;
}

void	wait_and_print_exit_status(void)
{
	int	status;
	int	exitstatus;

	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
		printf("%d", exitstatus);
	}
}
