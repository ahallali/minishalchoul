/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilnex <lilnex@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:28:40 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/31 16:51:05 by lilnex           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		result[tmp++] = expand_dquotes(ft_strdup((const char *)n->content));
		n = n->next;
	}
	return ((result));
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
		result[tmp++] = expand_dquotes(ft_strdup((const char *)n->content));
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
	if (!exec_env)
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

t_list	*get_exec(t_parse_utils *u)
{
	t_lex			*tmp;
	t_list			*l_tmp;
	t_list			*result;
	t_exec_utils	*exec;

	l_tmp = u->list_cmds;
	exec = init_exec_utils();
	result = NULL;
	while (l_tmp && exec)
	{
		tmp = l_tmp->content;
		if (tmp->type == 1)
			exec->cmd = tmp->command_name;
		else if (tmp->type == 2)
			ft_lstadd_back(&exec->args, ft_lstnew(tmp->variable));
		else if ((tmp->type == 5 || tmp->type == 7) && tmp->filename)
			convert_input_redirection(tmp, exec);
		else if ((tmp->type == 6 || tmp->type == 8) && tmp->filename)
			convert_output_redirection(tmp, exec);
		if (!handle_pipe(tmp, l_tmp, &exec, &result))
			return (NULL);
		l_tmp = l_tmp->next;
	}
	ft_lstadd_back(&result, ft_lstnew(exec));
	return (result);
}
