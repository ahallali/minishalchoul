/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:00:23 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 16:22:49 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lex(void *lex)
{
	t_lex	*_lex;

	_lex = (t_lex *)lex;
	printf("TYPE : %d\n", _lex->type);
	printf("CMD  : %s\n", _lex->command_name);
	printf("VAR  : %s\n", _lex->variable);
	printf("FILE : %s\n", _lex->filename);
	printf("--------------\n");
}

void	print_arg(void *arg)
{
	char	*str;

	str = (char *)arg;
	printf("ARG : %s\n", str);
}

void	print_exec(void *exec)
{
	t_exec_utils	*_exec;

	_exec = (t_exec_utils *)exec;
	printf("CMD : %s\n", _exec->cmd);
	printf("INF : %s\n", _exec->infile);
	printf("OUT : %s\n", _exec->outfile);
	printf("IN_FD : %d\n", _exec->input_fd);
	printf("OUT_FD : %d\n", _exec->output_fd);
	ft_lstiter(_exec->args, print_arg);
	printf("--------------\n");
}

t_exec_utils	*init_exec_utils(void)
{
	t_exec_utils	*exec;

	exec = ft_calloc(1, sizeof(t_exec_utils));
	if (!exec)
		return (exec);
	exec->input_fd = -1;
	exec->output_fd = -1;
	return (exec);
}
