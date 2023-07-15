/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:53 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/15 21:05:57 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	open_file(char *filename, int flags)
{
	int	fd;

	printf("opening with flag : %d\n", flags);
	fd = open(filename, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	printf("fd %d\n", fd);
	if (fd < 0)
		perror("Error redirection");
	return (fd);
}

void	convert_input_redirection(t_lex *tmp, t_exec_utils *exec)
{
	if (tmp->filename && tmp->type == 7)
	{
		close_last_fd(exec->inputFd);
		exec->inputFd = get_heredoc_fd(tmp->filename);
	}
	else if (tmp->filename)
	{
		close_last_fd(exec->inputFd);
		exec->inputFd = open_file(expand_dquotes(tmp->filename),
				tmp->flag_infile);
	}
	else if (tmp->fd != -1)
	{
		close_last_fd(exec->inputFd);
		exec->inputFd = tmp->fd;
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
		close_last_fd(exec->outputFd);
		exec->outputFd = open_file(expand_dquotes(tmp->filename),
				tmp->flag_outfile);
	}
	else if (tmp->fd != -1)
	{
		close_last_fd(exec->outputFd);
		exec->outputFd = tmp->fd;
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
		return (perror("Syntax Error: Expected command after pipe"), 0);
	if (tmp->type == PIPE)
	{
		ft_lstadd_back(result, ft_lstnew(*exec));
		*exec = init_exec_utils();
		return (1);
	}
	return (1);
}

t_list	*get_exec(t_parse_utils *u)
{
	t_lex			*tmp;
	t_list			*l_tmp;
	t_list			*result;
	t_exec_utils	*exec;

	l_tmp = u->list_cmds;
	exec = init_exec_utils();
	result = NULL;
	while (l_tmp && exec)
	{
		tmp = l_tmp->content;
		if (tmp->type == 1)
			exec->cmd = tmp->command_name;
		else if (tmp->type == 2)
			ft_lstadd_back(&exec->args, ft_lstnew(tmp->variable));
		else if ((tmp->type == 5 || tmp->type == 7) && tmp->filename)
			convert_input_redirection(tmp, exec);
		else if ((tmp->type == 6 || tmp->type == 8) && tmp->filename)
			convert_output_redirection(tmp, exec);
		if (!handle_pipe(tmp, l_tmp, &exec, &result))
			return (NULL);
		l_tmp = l_tmp->next;
	}
	ft_lstadd_back(&result, ft_lstnew(exec));
	return (result);
}
