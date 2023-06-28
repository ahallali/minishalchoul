/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/28 16:59:11 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int main (int ac,char **av,char** env)
{
	(void)ac;
	(void)av;
	char *line = NULL;
	int flag = 0;
	char * path;
	int tmp[2];
	t_parse_utils *p_prompt;

	tmp[0] = -1;
	tmp[1] = -1;
	minishell = ft_calloc(1, sizeof(t_minishell));

	minishell->env=NULL;
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

			ft_putstr_fd("exit\n",STDIN_FILENO);
			exit(0);
		}
		while (!line || !*line)
			line =readline("minishell>>");
		if (line && *line)
			add_history(line);//
		if (strcmp(line, "exit")==0)
		{
		    free (line);
		    break;
		}
		if (strcmp(line, "exit")==0)
		{
			free (line);
			break;
		}          
		if (line && *line)
			add_history(line);//
		p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		char *p_clean = ft_strtrim(line, " ");
		p_prompt->prompt = ft_strdup(p_clean);
		minishell->list_exec= parse_prompt(p_prompt->prompt , p_prompt);
		// ft_lstiter(minishell->list_exec, print_exec);

	
		while (minishell->list_exec)
		{		
				minishell->list = (t_exec_utils *)minishell->list_exec->content;
				if (!minishell->list->cmd)
					break;
				if (!minishell->list_exec->next)
					tmp[1] = 1;
				if (is_builtin(minishell))
					do_builtin(minishell);
				else
				{
					if (convert_args(minishell->list->args))
					{
						// printf("%s\n",path);
						path = update_path(path_finder(minishell->env, "PATH"), minishell->list->cmd);
						if (pipe(tmp) == 0 && path)
						{
							// printf("%d\n",minishell->list->inputFd);
							child(minishell, &flag, tmp, path);
							// printf("%d\n",minishell->list->inputFd);
							
							if (flag != 0)
								close(minishell->fd_out);
							minishell->fd_out = dup(tmp[0]);
							// close(tmp[0]);
							close(tmp[1]);
							
						}
					}
				}	
				minishell->list_exec = minishell->list_exec->next;
			while (wait(NULL) != -1)
					;
		}
	}	
}
				// printf("here\n");
		// line =readline("minishell>>");
		// free(tmp);
	// print_list(new);
	// CD && PWD && ENV BUILTIN DONE
	//  else if (strcmp(t[0], "exit") == 0)
	//      ft_exit (new,t[1]);
	// any builtin before  pipe executed on child 
