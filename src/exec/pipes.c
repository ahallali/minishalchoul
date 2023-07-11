/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:59:44 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/11 02:55:46 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	is_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->list->cmd, "cd", 3) == 0 || \
		(ft_strncmp(minishell->list->cmd, "env", 3) == 0 \
		&& ft_lstsize(minishell->list->args) == 0) \
		|| ft_strncmp(minishell->list->cmd, "pwd", 3) == 0 \
		|| ft_strncmp(minishell->list->cmd, "exit", 4) == 0 || \
		(ft_strncmp(minishell->list->cmd, "unset", 5) == 0 && \
		ft_lstsize(minishell->list->args)) || \
		(ft_strncmp(minishell->list->cmd, "echo", 4) == 0) || \
		(ft_strncmp(minishell->list->cmd, "export", 6) == 0))
		return (1);
	return (0);
}

void	ft_exit(t_minishell *minishell, char **cmd)
{
	(void)minishell;

	printf("%p\n", cmd[2]);
	if (!check_cmd_num(cmd[1]))
	{
		ft_putstr_fd("minishell>:exit:numeric argument required\n", 2);
		exit(ft_atoi(cmd[1]));
	}
	else if (cmd[2])
		ft_putstr_fd("minishell>: exit: too many arguments\n", 2);
	else if (!cmd[1] || !cmd[1][0])
	{	
	ft_putstr_fd("exit", 2);
	exit(0);
	}
}

int	check_cmd_num(char *cmd)
{
	int	i;
	if (!cmd || !*cmd)
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}
