/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_hyphen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:11:50 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/08 00:22:17 by ahallali         ###   ########.fr       */
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
				set_env("OLDPWD", pwd);
				set_env("PWD", oldpwd);
				printf("%s\n", oldpwd);
			}
		}
	}
}
