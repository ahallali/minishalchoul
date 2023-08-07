/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/08 00:06:14 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*movetodirectory(char *str, t_node *head)
{
	t_node	*new;
	char	*t;
	char	*oldpwd;

	t = NULL;
	new = head;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd)
		add_gcol(oldpwd);
	if (!str)
		return (NULL);
	if (!oldpwd)
		oldpwd = get_node(g_minishell->env, "PWD")->value;
	if (oldpwd)
		update_directory(str, oldpwd, t);
	return (new);
}

t_node	*update_env(t_node *head, char *var, char *data)
{
	t_node	*t;

	t = head;
	if (!data)
		return (head);
	while (t && t->next)
	{
		if (!ft_strcmp(t->variable, var))
			t->value = ft_strdup(data);
		t = t->next;
	}
	return (head);
}

int	set_env(char *var, char *value)
{
	insert_node(&g_minishell->env, value, var);
	insert_node(&g_minishell->export, value, var);
	return (1);
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
		{
			tmp = g_minishell->home;
			ft_putstr_fd("minishell : cd :HOME not set\n", 2);
			g_minishell->last_exitstatus = 1;
		}
		if (chdir(tmp) == 0)
		{
			set_env("OLDPWD", path_finder(head->env, "PWD"));
			set_env("PWD", tmp);
			g_minishell->pwd_stored = tmp;
		}
	}
	return (new);
}

void	tilda_and_movetodirectory(char **t, t_minishell *head,
				char *tmp, t_node *new)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = NULL;
	if (t[0][0] == '~')
	{
		oldpwd = path_finder(head->env, "PWD");
		if (path_finder(head->env, "HOME"))
			tmp = path_finder(head->env, "HOME");
		else
			tmp = g_minishell->home;
		if (chdir(tmp) == 0)
		{
			set_env("OLDPWD", oldpwd);
			set_env("PWD", tmp);
			g_minishell->pwd_stored = tmp;
		}
		return ;
	}
	else if (t[0][0] == '-')
		go_to_oldpwd(oldpwd, pwd);
	else
		new = movetodirectory(t[0], head->env);
}
