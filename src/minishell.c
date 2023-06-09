/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/09 15:27:41 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_minishell *minishell;
int main (int ac,char **av,char** env)
{
	(void)ac;
	(void)av;
	// char **t = NULL;
	// int status;
	// pid_t pid = fork();
	char *line = NULL;
	t_parse_utils *p_prompt;

	minishell = malloc (sizeof (t_minishell));
	minishell->env=NULL;
	if (!minishell)
		return (0);
	if (*env)
		minishell->env = ft_env(env);
	else 
		minishell->env = ft_empty();// to update
	update_env(minishell->env,"OLDPWD",NULL);
	while (1)
	{
		line = readline("minishell>>");
		if (!line )
			ft_putstr_fd("exit\n",STDIN_FILENO);
			// exit(0);
		while (!line || !*line)
			line =readline("minishell>>");
		if (line && *line)
			add_history(line);//
		if (strcmp(line, "exit")==0)
		{
		    free (line);
		    break;
		}
		// p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		// char *p_clean = ft_strtrim(" echo \"hel | lo\" ", " ");
		// char *p_clean = ft_strtrim(" ls|grep x", " ");
		// char *p_clean = ft_strtrim(line, " ");
		// p_prompt->prompt = ft_strdup(p_clean);
		// parse_prompt(p_prompt->prompt , p_prompt);
		if (strcmp(line, "exit")==0)
		{
			free (line);
			break;
		}          
		if (line && *line)
			add_history(line);//
		p_prompt = ft_calloc(1, sizeof(t_parse_utils));
		// char *p_clean = ft_strtrim(" echo \"hel | lo\" ", " ");
		// char *p_clean = ft_strtrim(" ls|grep x", " ");
		char *p_clean = ft_strtrim(line, " ");
		p_prompt->prompt = ft_strdup(p_clean);
		minishell->list_exec= parse_prompt(p_prompt->prompt , p_prompt);
		ft_lstiter(minishell->list_exec, print_exec);
		// convert_args(minishell->list->args);

		// printf("t == %c\n", *t[0]);
		// printf("t == %c\n", *t[1]);
		// printf("t == %s\n",t[2]);
		while (minishell->list_exec)
		{
				minishell->list = (t_exec_utils *)minishell->list_exec->content;
				if (!minishell->list_exec || !minishell->list->cmd || !*minishell->list->cmd)
					line =readline("minishell>>");
				else if (strcmp(minishell->list->cmd ,"cd")==0)
					ft_cd(minishell, convert_args(minishell->list->args));
				else if (strcmp(minishell->list->cmd,"env")==0 && ft_lstsize(minishell->list->args) == 0)
					print_list( minishell->env);
				else if (strcmp(minishell->list->cmd, "pwd") == 0)
					ft_pwd( minishell->env,"PWD");
				else if (ft_strncmp(minishell->list->cmd, "unset",5) == 0  && ft_lstsize(minishell->list->args) == 1)
					ft_unset(minishell->env,convert_args(minishell->list->args)[0]);
				else if (strcmp(minishell->list->cmd, "echo") == 0)
					ft_echo (convert_args(minishell->list->args),STDOUT_FILENO);
				else
				{
					if (convert_args(minishell->list->args))
						update_path(path_finder(minishell->env, "PATH"), minishell->list->cmd, convert_command_args(minishell->list), convert_env(minishell->env));
					// open(minishell->list->outfile, 777);
					// printf("%d", fd);
					// dup2(STDOUT_FILENO, fd);
					// printf("%s",convert_args(minishell->list->args)[1]);
					// puts("lalalal");
					// else
					// 	update_path(path_finder(minishell->env, "PATH"),minishell->list->cmd,NULL,convert_env(minishell->env));
				// 	break;
				// }
				}
				minishell->list_exec = minishell->list_exec->next;
						
				// else
				// {	
				// printf("%d",pid);
				// waitpid(pid, &status, WUNTRACED | WCONTINUED);
				// }
		}
		// line =readline("minishell>>");
	}
}
	// print_list(new);
	// CD && PWD && ENV BUILTIN DONE
	
	//  // else if (ft_strncmp(t[0], "export",6) == 0)
	//  //     ft_export(new,t[1]);
		
	//  else if (strcmp(t[0], "exit") == 0)
	//      ft_exit (new,t[1]);