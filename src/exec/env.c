/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:35:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:19:14 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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

	new = create_node(value, variable);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
	current->next = new;
	}
}

// static int shlvl = 1;
t_node	*ft_env(char **env, t_minishell *minishell)
{
	t_node	*head;
	char	*tmp;
	char	*value;
	char	*variable;

	head = NULL;
	tmp = NULL;
	while (*env)
	{
		tmp = ft_strchr(*env, '=');
		if (tmp != NULL)
		{
			*tmp = '\0';
			value = tmp + 1;
			variable = *env;
			insert_node(&head, value, variable);
			insert_node(&minishell->export, value, variable);
		}
		env++;
	}
	return (head);
}
