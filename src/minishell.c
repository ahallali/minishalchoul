/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/05 02:01:13 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line = NULL;
	int flag = 0;
	char *path;

	t_parse_utils *p_prompt;
	int read_f_pipe = 0;
	int old_pipe_fd =0;

	pid_t pid;

	minishell = ft_calloc(1, sizeof(t_minishell));

	minishell->env = NULL;
	if (!minishell)
		return (0);
	if (*env)
		minishell->env = ft_env(env);
	else
		minishell->env = ft_empty();
	while (1)
	{
		line = readline("minishell>>");
		if (!line)
		{

			ft_putstr_fd("exit\n", STDIN_FILENO);
			exit(0);
		}
		// while (!line || !*line)
		// 	line =readline("minishell>>");
		if (line && *line)
			add_history(line); //
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		if (line && *line)
			add_history(line); //
		p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		char *p_clean = ft_strtrim(line, " ");
		p_prompt->prompt = ft_strdup(p_clean);
		minishell->list_exec = parse_prompt(p_prompt->prompt, p_prompt);
		// ft_lstiter(minishell->list_exec, print_exec);

		int fd[2];
		while (minishell->list_exec)
		{
			minishell->list = (t_exec_utils *)minishell->list_exec->content;
			if (!minishell->list->cmd)
				break;
			if (is_builtin(minishell))
				do_builtin(minishell);
			else
			{
				if (minishell->list_exec->next)
				{
					if (pipe(fd) < 0)
					{
						perror("pipe");
						exit(1);
					}
				}
				pid = fork();
				if (pid < 0)
				{
					perror("fork");
					exit(1);
				}
				if (pid == 0)
				{
					if (minishell->list_exec->next)
					{	
						// puts("dup tmp 1 output");
							dup2(fd[1], 1);
							close(fd[0]);
					}
					else if (read_f_pipe == 1)
					{
						// puts("dup old pipe to 0");
						dup2(old_pipe_fd, 0);
						// close(0);
					}
					close(fd[1]);
					path = update_path(path_finder(minishell->env, "PATH"), minishell->list->cmd);
					if (path)
					{
						if (execve(path, convert_command_args(minishell->list), convert_env(minishell->env)) == -1)
							perror("execve");
					}
				}
				else
				{
					close(fd[1]);
					close(fd[0]);
					if (read_f_pipe == 1)
                    	close(old_pipe_fd);
					old_pipe_fd = fd[0]; 
					read_f_pipe = 1;
				}
			}
			minishell->list_exec = minishell->list_exec->next;
		}
		while (waitpid(-1, 0, 0) != -1)
			;
		// printf()
		int status;
		waitpid(pid, &status, 0);
	}
}
// 	if (convert_args(minishell->list->args))
// 	{
// 		path = update_path(path_finder(minishell->env, "PATH"), minishell->list->cmd);
// 		if (pipe(fd) == 0 && path) // PARENT // 0 1 2 fd[0] fd[1]
// 		{
// 			child(minishell, &flag, tmp, path);
// 			// if (flag != 0)
// 			// close(minishell->fd_out);
// 			// minishell->fd_out = dup(tmp[0]);
// 			// close(tmp[0]);
// 			close(tmp[1]);

// 		}
// 	}
// }
// minishell->list_exec = minishell->list_exec->next;
// printf("here\n");
// line =readline("minishell>>");
// free(tmp);
// print_list(new);
// CD && PWD && ENV BUILTIN DONE
//  else if (strcmp(t[0], "exit") == 0)
//      ft_exit (new,t[1]);
// any builtin before  pipe executed on child
