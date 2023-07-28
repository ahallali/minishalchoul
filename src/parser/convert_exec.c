/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:53 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/28 01:36:11 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (perror("Error redirection"), \
			g_minishell->last_exitstatus = 1,
			g_minishell->sigint_flag = 1, -1);
	return (fd);
}

void	convert_input_redirection(t_lex *tmp, t_exec_utils *exec)
{
	if (tmp->filename && tmp->type == 7)
	{
		close_last_fd(exec->input_fd);
		exec->input_fd = get_heredoc_fd(tmp->filename);
	}
	else if (tmp->filename)
	{
		close_last_fd(exec->input_fd);
		exec->input_fd = open_file(expand_dquotes(tmp->filename), \
			tmp->flag_infile);
	}
	else if (tmp->fd != -1)
	{
		close_last_fd(exec->input_fd);
		exec->input_fd = tmp->fd;
	}
	exec->infiles = tmp->infiles;
	if (ft_lstsize(exec->infiles))
		exec->infile = ft_lstlast(exec->infiles)->content;
	exec->flag_infile = tmp->flag_infile;
}

void	close_last_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	convert_output_redirection(t_lex *tmp, t_exec_utils *exec)
{
	if (tmp->filename)
	{
		close_last_fd(exec->output_fd);
		exec->output_fd = open_file(expand_dquotes(tmp->filename), \
									tmp->flag_outfile);
	}
	else if (tmp->fd != -1)
	{
		close_last_fd(exec->output_fd);
		exec->output_fd = tmp->fd;
	}
	exec->outfiles = tmp->outfiles;
	if (ft_lstsize(exec->outfiles))
		exec->outfile = ft_lstlast(exec->outfiles)->content;
	exec->flag_outfile = tmp->flag_outfile;
}

int	handle_pipe(t_lex *tmp, t_list *l_tmp,
				t_exec_utils **exec, t_list **result)
{
	if (tmp->type == PIPE && !l_tmp->next)
		return (perror("Syntax Error: Expected command after pipe"), \
		g_minishell->last_exitstatus = 258, 0);
	if (tmp->type == PIPE)
	{
		ft_lstadd_back(result, ft_lstnew(*exec));
		*exec = init_exec_utils();
		return (1);
	}
	return (1);
}
