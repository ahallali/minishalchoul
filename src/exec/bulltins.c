/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/24 19:08:47 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n_arg(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strwc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			printf("%c", str[i]);
		}
		i++;
	}
	return (0);
}

void	check_echo_arg(char **str, int fd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_check_n(str[i]) && !count)
			count = -1;
		if (*str[i] == '-' && (ft_check_n(str[i]) == 0) && count != -1)
		{
			count++;
			i++;
			continue ;
		}
		ft_putstr_fd(str[i], fd);
		if (str[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (count <= 0)
		ft_putstr_fd("\n", fd);
}

void	ft_echo(char **str, int fd)
{
	if (!str || !*str)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	check_echo_arg(str, fd);
}

t_node	*ft_empty(void)
{
	t_node		*head;
	char		*pwd;
	static int	shlvl;

	shlvl = 1;
	head = NULL;
	pwd = getcwd(NULL, 0);
	insert_node(&head, pwd, "PWD");
	insert_node(&head, ft_itoa(shlvl), "SHLVL");
	insert_node(&head, "/usr/bin/env", "_");
	free(pwd);
	return (head);
}
