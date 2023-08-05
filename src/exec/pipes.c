/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:59:44 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/04 23:42:42 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_msg(char **cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell>: exit: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	is_builtin(t_minishell *g_minishell)
{
	if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "cd") || \
		(ft_strequals(expand_dquotes(g_minishell->list->cmd), "env") && \
		ft_lstsize(g_minishell->list->args) == 0) || \
		ft_strequals(expand_dquotes(g_minishell->list->cmd), "pwd") || \
		ft_strequals(expand_dquotes(g_minishell->list->cmd), "exit") || \
		(ft_strequals(expand_dquotes(g_minishell->list->cmd), "unset")) || \
		(ft_strequals(expand_dquotes(g_minishell->list->cmd), "echo")) || \
		(ft_strequals(expand_dquotes(g_minishell->list->cmd), "export")))
		return (1);
	return (0);
}

long long	custom_atoi(char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (sign * res);
}

int	is_inside_range(char *str)
{
	char	*llmax;
	char	*llmin;

	llmax = "9223372036854775807";
	llmin = "-9223372036854775807";
	if (ft_strlen(str) > ft_strlen(llmax))
		return (1);
	else if (ft_strlen(str) == ft_strlen(llmax))
	{
		if (ft_strncmp(str, llmax, ft_strlen(str)) > 0)
			return (1);
	}
	if (ft_strlen(str) > ft_strlen(llmin))
		return (1);
	else if (ft_strlen(str) == ft_strlen(llmin))
	{
		if (ft_strncmp(str, llmin, ft_strlen(str)) > 0)
			return (1);
	}
	return (0);
}

void	ft_exit(t_minishell *g_minishell, char **cmd)
{
	int	flag;

	flag = 0;
	if (!g_minishell->list->cmd || !*g_minishell->list->cmd)
		return ;
	if (!cmd[0] || !*cmd[0])
		exit(0);
	if (check_cmd_num(cmd[0]) && !cmd[1])
	{
		print_msg(cmd);
		do_clean_exit(NULL, 2, 255, 1);
	}
	else if (!is_inside_range(cmd[0]))
	{
		print_msg(cmd);
		exit(255);
	}
	else if (cmd[0] && cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell>: exit: too many arguments\n", 2);
		g_minishell->last_exitstatus = 1;
	}
	else
		do_clean_exit(NULL, 1, custom_atoi(cmd[0]) % 256, 0);
}
