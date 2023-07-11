/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:35:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/10 17:20:51 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_node	*create_node(char *value, char *variable)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
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
t_node	*ft_env(char **env)
{
	t_node	*head;
	char	*tmp;
	char	*value;
	char	*variable;
	// static int shlvl ;

	head = NULL;
	tmp = NULL;
	while (*env)
	{
		tmp = ft_strchr(*env, '=');
		if (tmp != NULL)
		{
			*tmp = '\0';
			if (!ft_strncmp(*env, "SHLVL=",6))
			{
				value = ft_itoa(ft_atoi(tmp));
				// variable = *env;
			}
			else 
			value = tmp + 1;
			variable = *env;
			insert_node(&head, value, variable);
		}
		env++;
	}
	return (head);
}

// void	swap_nodes(t_node **head , t_node  *n,t_node *m)
// {
// 	struct s_node	*tmp;
// 	t_node			*pre_n;
// 	t_node *pre_m;
// 			pre_m = NULL;
// 	t_node *current=*head;
// 	if (n==m || !n || !m )
// 		return ;

// 	*pre_n = NULL;
// 	while (current && (pre_n != NULL || pre_m != NULL))
// 	{
// 		if (current->next == n)
// 			pre_n = current;
// 		else if (current->next == m)
// 			pre_m = current;
// 		current = current->next;
// 	}
// 	if (pre_n == NULL || pre_m == NULL)
// 		return ;
// 	if (pre_n != NULL)
// 		current->next = pre_m;
// 	else
// 		*head = m;
// 	if (pre_m != NULL)
// 		current->next = pre_n;
// 	else
// 		*head = n;
// 	tmp = n->next;
// 	n->next = m->next;
// 	m->next = tmp;
// }
