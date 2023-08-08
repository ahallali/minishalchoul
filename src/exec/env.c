/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:35:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/08 00:31:11 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_node(char *value, char *variable)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	if (!value)
		new->value = value;
	else
		new->value = ft_strdup(value);
	new->variable = ft_strdup(variable);
	new->next = NULL;
	return (new);
}

void	insert_node(t_node **head, char *value, char *variable)
{
	t_node	*new;
	t_node	*current;

	if (!variable)
		return ;
	new = create_node(value, variable);
	if (value)
		value = ft_strdup(value);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL || \
		ft_strequals(current->variable, variable))
		{
			if (ft_strequals(current->variable, variable))
			{
				current->value = value;
				return ;
			}
			current = current->next;
		}
		current->next = new;
	}
}

void	fill_export_env(t_node **head)
{
	char	**keys;
	t_node	*node;

	keys = ft_calloc(count_nodes(*head) + 1, sizeof(char *));
	if (!keys)
		return ;
	fill_keys(keys, *head);
	sort_tab(keys, count_nodes(*head));
	while (keys && *keys)
	{
		node = get_node(*head, *keys++);
		insert_node(&g_minishell->export, node->value, node->variable);
	}
}

t_node	*ft_env(char **env, t_minishell *minishell)
{
	t_node	*head;
	char	*tmp;
	char	*value;
	char	*variable;

	(void)minishell;
	head = NULL;
	tmp = NULL;
	while (*env)
	{
		tmp = ft_strchr(*env, '=');
		if (tmp != NULL)
		{
			*tmp = '\0';
			if (!ft_strncmp(*env, "SHLVL", 6))
				value = ft_itoa(ft_atoi(tmp + 1) + 1);
			else
				value = tmp + 1;
			variable = *env;
			insert_node(&head, value, variable);
		}
		env++;
	}
	return (head);
}

void	ft_pwd(t_node *head, char *s)
{
	t_node	*t;
	char	*pwd;

	pwd = NULL;
	t = head;
	pwd = getcwd(NULL, 0);
	if (s || !t)
		get_pwd(pwd);
	else
		search_in_env(t, s);
}
