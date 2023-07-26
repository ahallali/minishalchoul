/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 02:09:20 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/26 16:31:51 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	error_exec(char *path)
{
	if (is_path_directory(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		do_clean_exit(NULL, 2, 126, 1);
	}
	else if (errno == EACCES)
	{
		perror("minishell");
		do_clean_exit(NULL, 2, 126, 1);
	}
	else if (errno == EISDIR)
		ft_putstr_fd("minishell:is a directory\n", 2);
	else if (errno == 14)
	{
		do_clean_exit("minishell: command not found\n", 2, 127, 1);
	}
	else if (errno == ENOENT)
		ft_putstr_fd("minishell:No such file or directory\n", 2);
	else
		perror("minishell");
	do_clean_exit(NULL, 2, 126, 1);
}

void	do_clean_exit(char *error_msg, int fd, int exit_status, int flag)
{
	t_list	**node;

	node = get_gcollector();
	if (error_msg)
		ft_putstr_fd(error_msg, fd);
	ft_lstiter(*node, ft_free);
	if (!flag)
		ft_putstr_fd("exit\n", fd);
	if (exit_status >= 0)
		exit(exit_status);
}
