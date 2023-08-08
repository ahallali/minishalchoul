/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_hyphen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:11:50 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/08 00:59:03 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_to_oldpwd(char *oldpwd, char *pwd)
{
	oldpwd = path_finder(g_minishell->env, "OLDPWD");
	if (!oldpwd || !*oldpwd)
	{
		ft_putstr_fd("minishell :cd : OLDPWD not set\n", 2);
		g_minishell->last_exitstatus = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		add_gcol(pwd);
		if (pwd)
		{
			if (chdir(oldpwd) == 0)
			{
				set_env("OLDPWD", pwd, 0);
				set_env("PWD", oldpwd, 0);
				printf("%s\n", oldpwd);
			}
		}
	}
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
			tmp = ft_str_replace(t[0], "~", path_finder(head->env, "HOME"), 0);
		else
			tmp = ft_str_replace(t[0], "~", g_minishell->home, 0);
		if (chdir(tmp) == 0)
		{
			set_env("OLDPWD", oldpwd, 9);
			set_env("PWD", tmp, 0);
			g_minishell->pwd_stored = tmp;
		}
		return ;
	}
	else if (t[0][0] == '-')
		go_to_oldpwd(oldpwd, pwd);
	else
		new = movetodirectory(t[0], head->env);
}
