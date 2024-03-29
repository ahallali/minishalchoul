/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/04 01:00:13 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(char *str)
{
	if (str)
		free(str);
}

void	ft_unset_norm(t_node **head, t_node *t, t_node *tmp, char *var)
{
	while (t)
	{
		if (!ft_strncmp(t->variable, var, ft_strlen(t->variable)) && \
			ft_strncmp(t->variable, "_", 1))
		{
			if (t == *head)
			{
				*head = t->next;
				t = *head;
			}
			else
			{
				tmp->next = t->next;
				t = tmp->next;
			}
		}
		else
		{
			tmp = t;
			t = t->next;
		}
	}
}

void	ft_unset(t_node **head, char *var)
{
	t_node	*t;
	t_node	*tmp;

	tmp = NULL;
	t = *head;
	if (!head || !var)
		return ;
	ft_unset_norm(head, t, tmp, var);
}

void	builtin_next(t_minishell *g_minishell)
{
	if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "echo"))
		ft_echo(g_minishell->list->args, STDOUT_FILENO);
	else if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "exit"))
		ft_exit(g_minishell, convert_args(g_minishell->list->args));
	else if (ft_strequals(g_minishell->list->cmd, "export"))
		ft_export(g_minishell->list->args, g_minishell);
}

void	ft_unset_args(t_list *l_args)
{
	char	**args;
	int		i;

	i = 0;
	args = convert_args(l_args);
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			ft_putstr_fd("Not a valid identifier", 2);
			g_minishell->last_exitstatus = 1;
			return ;
		}
		ft_unset(&g_minishell->env, args[i]);
		ft_unset(&g_minishell->export, args[i]);
		i++;
	}
}
