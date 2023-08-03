/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/04 00:22:30 by ichaiq           ###   ########.fr       */
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

int	print_echo_arg(t_list *node, int *count, int *flag, int fd)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	str = expand_dquotes(node->content);
	if (str)
	{
		if (*str == '-' && ft_strlen(str) > 1
			&& (ft_check_n(str) == 0) && *count != -1 && *flag == 0)
		{
			(*count)++;
			return (1);
		}
		else 
			*flag = 1;
		ft_putstr_fd(str, fd);
		if ((node->next && node->next->content))
			ft_putstr_fd(" ", fd);
	}
	return (0);
}

void	check_echo_arg(t_list *node, int fd)
{
	int		i;
	int		count;
	int		flag;
	t_list	*tmp;

	i = 0;
	count = 0;
	flag = 0;
	tmp = node;
	while (tmp)
	{
		// printf("\nreceived arg %s\n", ((char *)tmp->content));
		print_echo_arg(tmp, &count, &flag, fd);
		tmp = tmp->next;
	}
	if (count <= 0)
		ft_putstr_fd("\n", fd);
}

void	ft_echo(t_list *args, int fd)
{
	if (!args)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	check_echo_arg(args, fd);
	g_minishell->last_exitstatus = 0;
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
