/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:59:44 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/04 10:30:38 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

/*
bool read_from_pipe;
int	read_of_old_fd;

while (minishell->list_exec)
{
	fork();
	pipe(fd);
	read_of_old_fd = fd[0];
	if (child do) // 0 1 2 fd[0] fd[1]
	{
		if (we have a heredoc)
		{
			FIRST TO BE OPENNED AND STORE IT IN A FILE;
		}
		if (next_command)
			dup2(fd[1], 1);
		else if (read_from_pipe == 1)
		{	dup2(read_of_old_fd, 0);
			close(read_of_old_fd);
		}
		close(fd[1]);
		if (next_command == NULL)
			close(fd[0]);

		while (list_of_redirections)
		{
			//if last redirection dup before closing fd
			open(infile);
			close(infile);
			open(outfile);
			close(outfile);
			goto_next_redirection;
		}
		get_path();
		execve();
	}
	else(parent)
	{
		close(fd[1], fd[0]);
		goto_next_command; minishell->list_exec = minishell->list_exec-next;
		read_from_pipe = 1;
	}
}
wait_childs();
*/