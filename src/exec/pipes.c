/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:59:44 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 17:42:57 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_minishell *minishell)
{
	if (ft_strncmp(expand_dquotes(minishell->list->cmd), "cd", 3) == 0 || \
		(ft_strncmp(expand_dquotes(minishell->list->cmd), "env", 3) == 0 && \
		ft_lstsize(minishell->list->args) == 0) || \
		ft_strncmp(expand_dquotes(minishell->list->cmd), "pwd", 3) == 0 || \
		ft_strncmp(expand_dquotes(minishell->list->cmd), "exit", 4) == 0 || \
		(ft_strncmp(expand_dquotes(minishell->list->cmd), "unset", 5) == 0 && \
			ft_lstsize(minishell->list->args)) || \
		(ft_strncmp(expand_dquotes(minishell->list->cmd), "echo", 4) == 0) || \
		(ft_strncmp(expand_dquotes(minishell->list->cmd), "export", 6) == 0))
		return (1);
	return (0);
}

void	ft_exit(t_minishell *minishell, char **cmd)
{
	if (!minishell->list->cmd || !*minishell->list->cmd)
		return ;
	if (!cmd || !*cmd)
		exit(0);
	else if (cmd[0] && !check_cmd_num(cmd[0]) && !cmd[1])
	{
		ft_putstr_fd("minishell>:exit:numeric argument required\n", 2);
		exit(255);
	}
	else if (!cmd[1] && cmd[0] && check_cmd_num(cmd[0]))
		exit(ft_atoi(cmd[0]));
	else
		ft_putstr_fd("minishell>: exit: too many arguments\n", 2);
}

int	check_cmd_num(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}
