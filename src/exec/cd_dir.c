/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:46:28 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/08 00:47:53 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	for_norm(char *t, char *str, char *oldpwd)
{
	perror(join_cmd_err("minishell: "));
	if (check_str(str))
	{
		t = ft_strjoin(g_minishell->pwd_stored, ft_strjoin("/", str));
		insert_node(&g_minishell->env, t, "PWD");
		g_minishell->pwd_stored = t;
		g_minishell->last_exitstatus = 1;
		ft_free(oldpwd);
	}
	g_minishell->last_exitstatus = 1;
}

void	update_directory(char *str, char *oldpwd, char *t)
{
	if (chdir(str) == 0)
	{
		set_env("OLDPWD", oldpwd, 0);
		t = getcwd(NULL, 0);
		if (t)
		{
			set_env("PWD", t, 0);
			g_minishell->pwd_stored = ft_strdup(t);
			ft_free(t);
		}
		else
		{
			perror(ERRCD);
			if (check_str(str))
			{
				t = ft_strjoin(g_minishell->pwd_stored, ft_strjoin("/", str));
				set_env("PWD", t, 0);
				g_minishell->pwd_stored = ft_strdup(t);
			}
		}
	}
	else
		for_norm(t, str, oldpwd);
}

void	search_in_env(t_node *t, char *s)
{
	while (t->next)
	{
		if (!ft_strncmp(t->variable, s, ft_strlen(s))
			&& t->value)
		{
			ft_putstr_fd(t->value, 1);
			ft_putstr_fd("\n", 1);
			g_minishell->pwd_stored = ft_strdup(t->value);
			return ;
		}
		t = t->next;
	}
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.' || str[i] == '~' || (str[i] == '.' && str[i + 1] == '.'))
		return (1);
	return (0);
}

void	get_pwd(char *pwd)
{
	if (pwd != NULL)
	{
		g_minishell->pwd_stored = ft_strdup(pwd);
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		set_env("PWD", ft_strdup(pwd), 0);
		ft_free(pwd);
	}
	else
	{
		ft_putstr_fd(g_minishell->pwd_stored, 1);
		ft_putstr_fd("\n", 1);
		set_env("PWD", ft_strdup(g_minishell->pwd_stored), 0);
	}
}
