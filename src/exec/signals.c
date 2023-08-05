/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:28:25 by ahallali          #+#    #+#             */
/*   Updated: 2023/08/05 16:11:43 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	char	cr;

	(void)sig;
	cr = 13;
	if (g_minishell->heredoc_flag && sig == SIGINT)
	{
		g_minishell->sigint_flag = 1;
		write(STDIN_FILENO, &cr, 1);
	}
	if (g_minishell->runned)
		return ;
	g_minishell->last_exitstatus = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	if (!g_minishell->heredoc_flag)
		rl_redisplay();
}

char	*get_home(t_minishell *g_minishell)
{
	t_node	*tmp;
	char	*t;

	t = NULL;
	tmp = g_minishell->env;
	while (tmp)
	{
		if (ft_strequals(tmp->variable, "HOME"))
			t = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	return (t);
}

void	do_builtin(t_minishell *g_minishell)
{
	if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "cd"))
		ft_cd(g_minishell, convert_args(g_minishell->list->args));
	else if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "env") \
		&& ft_lstsize(g_minishell->list->args) == 0)
		print_list(g_minishell->env);
	else if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "pwd"))
		ft_pwd(g_minishell->env, "PWD");
	else if (ft_strequals(expand_dquotes(g_minishell->list->cmd), "unset") \
	&& ft_lstsize(g_minishell->list->args) >= 1)
		ft_unset_args(g_minishell->list->args);
	builtin_next(g_minishell);
}

void	print_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}
