/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_hyphen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:11:50 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/07 23:13:08 by ahallali         ###   ########.fr       */
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
		if (pwd)
		{
			if (chdir(oldpwd) == 0)
			{
				update_env(g_minishell->env, "OLDPWD", pwd);
				update_env(g_minishell->env, "PWD", oldpwd);
				printf("%s\n", oldpwd);
			}
		}
	}
}
