/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:47:03 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/16 01:24:13 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *get_node(t_node *head, char *key)
{
    t_node *tmp;

    tmp = head;
    while (tmp)
    {
        if (ft_strequals(tmp->variable, key))
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

t_node *update_node(char *key, char *value, int append)
{
    t_node *node;
    t_node *exp_node;

    node = get_node(minishell->env, key);
    if (!node)
    {
        insert_node(&minishell->env, value, key);
        insert_node(&minishell->export, value, key);
        return (get_node(minishell->env, key));
    }
    if (!append || !value || !node->value)
        node->value = value;
    else if (node->value)
        node->value = ft_strjoin(node->value, value);
    // else
    //     node->value = value;
    exp_node = get_node(minishell->export, node->variable);
    exp_node->value = node->value;
    return (node);
}

int	is_valid_key(char *var)
{
	int	i;

	i = 0;
	if (!var[i] || ft_isdigit(var[i++]))
		return (0);
	while (ft_isalpha(var[i]) || var[i] == 95 || ft_isdigit(var[i]))
		i++;
	if (!var[i] || var[i] == '=' || (var[i] == '+' && var[i + 1] == '='))
		return (1);
    printf("var %c\n", var[i]);
	return (0);
}



void parse_key_value(char *arg, char *op, int append)
{
    char *key;
    char *value;

    // printf("append : %d\n", append);
    key = ft_substr(arg, 0, op - arg - append);
    value = ft_substr(arg, op - arg + 1 , ft_strlen(arg));
    // printf("key : %s\n", key);
    // printf("value : %s\n", value);
    update_node(key, expand_dquotes(value), append);
}

void add_value(char *arg)
{
    char *op;
    int     append;
    
    append = 0;
	if (!is_valid_key(arg))
	{
		perror("not a valid identifier");
		return ;
	}
    op = ft_strchr(arg, '=');
	if (!op)
        update_node(arg, NULL, 0);
    else
	// printf("val : %s\n", value);
    {
        if (arg != op && *(op - 1) == '+')
            append = 1;
        parse_key_value(arg, op, append);
        
    }
        
}
