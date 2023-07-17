/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/17 22:42:19 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*movetodirectory(char *str, t_node *head)
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
		t = getcwd(NULL, 0);
		new = update_env(head, "PWD", t);
		}
		else
		{
			perror("getcwd: cannot access parent directories");
			g_minishell->last_exitstatus = 258;
		}
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
	while (t)
	{
		if (ft_strequals(t->variable, var))
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
		tilda_and_movetodirectory(t, head, tmp, new);
	else if (!t[0] || !*t[0])
	{
		if (path_finder(head->env, "HOME"))
			tmp = path_finder(head->env, "HOME");
		else
			tmp = g_minishell->home;
		if (chdir(tmp) == 0)
		{	
			update_env(head->env, "OLDPWD", path_finder(head->env, "PWD"));
			new = update_env(head->env, "PWD", tmp);
		}
	}
	return (new);
}

void	tilda_and_movetodirectory(char **t, t_minishell *head, \
char *tmp, t_node *new)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (t[0][0] == '~')
	{
		oldpwd = path_finder(head->env, "OLDPWD");
		if (path_finder(head->env, "HOME"))
			tmp = path_finder(head->env, "HOME");
		else
			tmp = g_minishell->home;
		if (chdir(tmp) == 0)
		{
			head->env = update_env(head->env, "OLDPWD", \
			oldpwd);
			head->env = update_env(head->env, "PWD", tmp);
		}
		return ;
	}
	else
		new = movetodirectory(t[0], head->env);
}
