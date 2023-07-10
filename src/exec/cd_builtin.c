/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/10 01:29:42 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*gt(char *str, t_node *head)
{
	t_node	*new;
	char	*t;
	char	*oldpwd;

	new = head;
	oldpwd = getcwd(NULL, 0);
	if (chdir(str) == 0)
	{
		update_env(head, "OLDPWD", oldpwd);
		if (getcwd(NULL, 0) != NULL)
		{	
		t = getcwd(NULL,0);
		new = update_env(head, "PWD", t);
		}
		else
			perror("getcwd: cannot access parent directories");
		return (new);
	}
	else
	{
		perror(str);
		return (NULL);
	}
}

t_node	*update_env(t_node *head, char *var, char *data)
{
	t_node	*t;

	t = head;
	while (t->next)
	{
		if (!strcmp(t->variable, var))
			t->value = data;
		t = t->next;
	}
	return (head);
}

char	*path_finder(t_node *head, char *var)
{
	t_node	*t;

	t = head;
	if (!head)
		return (NULL);
	while (t->next)
	{
		if (!strcmp(t->variable, var))
			return (t->value);
	t = t->next;
	}
	return (NULL);
}

t_node	*ft_cd(t_minishell *head, char **t)
{
	t_node	*new;
	char	*tmp;

	new = NULL;
	tmp = NULL;
	if (t[0] && *t[0])
	{
		if (t[0][0] == '~')
		{
			if (path_finder(head->env, "HOME"))
				tmp = path_finder(head->env, "HOME");
			if (chdir(tmp) == 0)
				return (NULL);
			else
			{
			head->env = update_env(head->env, "OLDPWD", \
				path_finder(head->env, "PWD"));
			head->env = update_env(head->env, "PWD", tmp);
			}
		}
		else
			new = gt(t[0], head->env);
	}
	else if (!t[0] || !*t[0])
	{
		if (path_finder(head->env, "HOME"))
			tmp = path_finder(head->env, "HOME");
		if (chdir(tmp) == 0)
		{	
			update_env(head->env, "OLDPWD", path_finder(head->env, "PWD"));
			new = update_env(head->env, "PWD", tmp);
		}
	}
	return (new);
}
