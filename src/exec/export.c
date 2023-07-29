/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilnex <lilnex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:47:03 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/29 19:33:34 by lilnex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*get_node(t_node *head, char *key)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strequals(tmp->variable, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_node	*update_node(char *key, char *value, int append)
{
	t_node	*node;
	t_node	*exp_node;

	node = get_node(g_minishell->env, key);
	if (!node)
	{
		insert_node(&g_minishell->env, value, key);
		insert_node(&g_minishell->export, value, key);
		return (get_node(g_minishell->env, key));
	}
	if (!append || !value || !node->value)
		node->value = value;
	else if (node->value)
		node->value = ft_strjoin(node->value, value);
	exp_node = get_node(g_minishell->export, node->variable);
	exp_node->value = node->value;
	return (node);
}

int	is_valid_key(char *var)
{
	int	i;

	i = 0;
	if (!var[i]
		|| !((ft_isalpha(var[i]) || var[i] == 95) || ft_isdigit(var[i++])))
		return (0);
	while (ft_isalpha(var[i]) || var[i] == 95 || ft_isdigit(var[i]))
		i++;
	if (!var[i] || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (1);
	return (0);
}

void	parse_key_value(char *arg, char *op, int append)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, op - arg - append);
	value = ft_substr(arg, op - arg + 1, ft_strlen(arg));
	update_node(key, expand_export(value), append);
}

void	add_value(char *arg, t_minishell *g_minishell)
{
	char	*op;
	int		append;

	append = 0;
	if (!is_valid_key(arg))
	{
		g_minishell->last_exitstatus = 1;
		return ;
	}
	op = ft_strchr(arg, '=');
	if (!op)
		update_node(arg, NULL, 0);
	else
	{
		if (arg != op && *(op - 1) == '+')
			append = 1;
		parse_key_value(arg, op, append);
	}
}
