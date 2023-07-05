/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/05 19:12:03 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_fds(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line = NULL;
	int flag = 0;
	char *path;
	int fd[2];
	int STDIN = -1;
	int STDOUT;
	int old_stdin = -1;
	t_parse_utils *p_prompt;
	int read_f_pipe = 0;
	int old_pipe_fd = 0;
	int pip = 0;

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
		p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		char *p_clean = ft_strtrim(line, " ");
		p_prompt->prompt = ft_strdup(p_clean);
		minishell->list_exec = parse_prompt(p_prompt->prompt, p_prompt);
		ft_lstiter(minishell->list_exec, print_exec);

	
		while (minishell->list_exec)
		{
				STDOUT = -1;
				minishell->list = (t_exec_utils *)minishell->list_exec->content;
				if (!minishell->list->cmd)
					break;
				if (minishell->list_exec->next)
				{
					// pip = 1;
					if (pipe(fd) < 0)
					{
						perror("pipe:");
						exit(1);
					}
					else
					{
						STDOUT = fd[1];
						old_stdin = fd[0];
					}
				}
				pid = fork();
				if (pid < 0)
				{
					perror("forkerror :");
					exit(1);
				}
				if (pid == 0)
				{
					dup2(STDIN, 0);
					close(STDIN);
					dup2(STDOUT, 1);
					close(STDOUT);
					close(fd[0]);
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
					close(STDIN);
					STDIN = old_stdin;
				}
		// if (pip)
			while (waitpid(-1, NULL, 0)!= -1);
		// pip = 0;
		minishell->list_exec = minishell->list_exec->next;
		}
	}
}
	// dup2(soutput_fd,1);
	// dup2(sinput_fd,0);
	// close(soutput_fd);
	// close(sinput_fd);
	// }
// printf("here\n");
// line =readline("minishell>>");
// free(tmp);
// print_list(new);
// CD && PWD && ENV BUILTIN DONE
//  else if (strcmp(t[0], "exit") == 0)
//      ft_exit (new,t[1]);
// any builtin before  pipe executed on child
