/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 17:09:32 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_node *head, char *s)
{
	t_node	*t;
	char	*pwd;

	pwd = NULL;
	t = head;
	if (!head)
	{
		pwd = getcwd(NULL, 0);
		update_env(head, "PWD", pwd);
	}
	if (t)
	{
		while (t->next)
		{
			if (!strcmp(t->variable, s) && t->value)
			{
				ft_putstr_fd(t->value, 1);
				ft_putstr_fd("\n", 1);
			}
			t = t->next;
		}
	}
}

void	print_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void	del(char *str)
{
	if (str)
		free(str);
}

t_node	*ft_unset(t_node **head, char *var)
{
	t_node	*t;
	t_node	*tmp;

	t = *head;
	if (!head || !var)
		return (NULL);
	while (t)
	{
		if (!ft_strncmp(t->variable, var, ft_strlen(t->variable)) \
		&& ft_strncmp(t->variable, "_", 1))
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
	return (t);
}

void	do_builtin(t_minishell *minishell)
{
	if (ft_strncmp(expand_dquotes(minishell->list->cmd), "cd", 2) == 0)
		ft_cd(g_minishell, convert_args(minishell->list->args));
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "env", 3) == 0 \
	&& ft_lstsize(minishell->list->args) == 0)
		print_list(minishell->env);
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "pwd", 3) == 0)
		ft_pwd(minishell->env, "PWD");
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "unset", 5) == 0 \
	&& ft_lstsize(minishell->list->args) == 1)
	{
		if (!is_valid_key(convert_args(minishell->list->args)[0]))
		{
			perror("Not a valid identifier");
			return ;
		}
		ft_unset(&minishell->env, convert_args(minishell->list->args)[0]);
		ft_unset(&minishell->export, convert_args(minishell->list->args)[0]);
	}
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "echo", 4) == 0)
		ft_echo(convert_args(minishell->list->args), STDOUT_FILENO);
	else if (ft_strequals(expand_dquotes(minishell->list->cmd), "exit"))
		ft_exit(minishell, convert_args(minishell->list->args));
	else if (ft_strncmp(minishell->list->cmd, "export", 6) == 0)
		ft_export(convert_args(minishell->list->args));
}
