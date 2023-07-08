/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/07 13:02:20 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *minishell;

int main (int ac, char **av, char** env)
{
	(void)ac;
	(void)av;
	char *line = NULL;
	int flag = 0;
	char *path;
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
		execute(minishell);
	}
}
// print_list(new);
// CD && PWD && ENV BUILTIN DONE
//  else if (strcmp(t[0], "exit") == 0)
//      ft_exit (new,t[1]);
// any builtin before  pipe executed on child
