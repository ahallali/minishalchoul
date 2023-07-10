/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/10 01:13:21 by ahallali         ###   ########.fr       */
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
	int	i ;

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

void	check_echo_arg(char **str, int i, int count, int fd)
{
	while (str[i])
	{
		if (*str[i] == '-' && (ft_check_n(str[i]) == 0))
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
}

void	ft_echo(char **str, int fd)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	if (!str || !*str)
	{
		flag = 1;
		ft_putstr_fd("\n", fd);
		return ;
	}
	check_echo_arg(str, i, count, fd);
	if (!count)
		ft_putstr_fd("\n", fd);
}

t_node	*ft_empty(void)
{
	t_node	*head;
	char	*pwd;

	head = NULL;
	pwd = getcwd(NULL, 0);
	insert_node(&head, pwd, "PWD");
	insert_node(&head, "1", "SHLVL");
	insert_node(&head, "/usr/bin/env", "_");
	return (head);
}
