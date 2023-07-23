/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/23 02:45:37 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *movetodirectory(char *str, t_node *head)
{
	t_node *new;
	char *t;
	char *oldpwd;

	new = head;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd && chdir(str) == 0)
	{
		update_env(g_minishell->env, "OLDPWD", oldpwd);
		t = getcwd(NULL, 0);
		insert_node(&g_minishell->env, t, "PWD");
		return (new);
	}
	else
	{

		g_minishell->last_exitstatus = 258;
		return (perror("getcwd: cannot access parent directories"), NULL);
	}
}

t_node *update_env(t_node *head, char *var, char *data)
{
	t_node *t;

	t = head;
	if (!data)
		return (head);
	while (t->next)
	{
		if (!strcmp(t->variable, var))
			t->value = data;
		t = t->next;
	}
	return (head);
}

char *path_finder(t_node *head, char *var)
{
	t_node *t;

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

t_node *ft_cd(t_minishell *head, char **t)
{
	t_node *new;
	char *tmp;

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
			insert_node(&g_minishell->env, tmp, "PWD");
		}
	}
	return (new);
}

void tilda_and_movetodirectory(char **t, t_minishell *head,
							   char *tmp, t_node *new)
{
	char *oldpwd;

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
			insert_node(&g_minishell->env, oldpwd, "OLDPWD");
			insert_node(&g_minishell->env, tmp, "PWD");
		}
		return;
	}
	else
		new = movetodirectory(t[0], head->env);
}
