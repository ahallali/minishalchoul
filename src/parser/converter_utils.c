/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:28:40 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/08 17:35:28 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**convert_args(t_list *node)
{
	int		len;
	int		tmp;
	char	**result;
	t_list	*n;

	len = ft_lstsize(node);
	result = NULL;
	tmp = 0;
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	n = node;
	while (n)
	{
		result[tmp++] = ft_strdup((const char *)n->content);
		n = n->next;
	}
	return (result);
}

char	**convert_command_args(t_exec_utils *utils)
{
	int		len;
	int		tmp;
	char	**result;
	t_list	*n;

	len = ft_lstsize(utils->args);
	result = NULL;
	tmp = 0;
	result = ft_calloc(len + 2, sizeof(char *));
	if (!result)
		return (NULL);
	result[tmp++] = utils->cmd;
	n = utils->args;
	while (n)
	{
		result[tmp++] = ft_strdup((const char *)n->content);
		n = n->next;
	}
	return (result);
}

char	**convert_env(t_node *node)
{
	char	**exec_env;
	int		i;
	t_node	*tmp;
	int		len;

	tmp = node;
	len = 0;
	i = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	exec_env = ft_calloc((len + 1), sizeof(char *));
	if (!exec_env || !*exec_env)
		return (NULL);
	while (i < len)
	{
		exec_env[i] = ft_strjoin(node->variable, ft_strjoin("=", node->value));
		node = node->next;
		i++;
	}
	exec_env[i] = NULL;
	return (exec_env);
}
