/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/26 12:30:51 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_n_arg(char *str)
{
  int i = 2;
  while (str[i])
  {
    if (str[i] != 'n')
        return (1);
    i++;
  }
  return (0);
}
int ft_strwc(char *str)
{
  int i = 0;
    while (str[i])
    {
        if (str[i] != '\"' && str[i]!= '\'')
        {
          printf("%c", str[i]);
        }
        i++;
    }
  return (0);
}



void ft_echo(char **str, int fd)
{
    int i = 0;
    int flag = 0;
    int count = 0;

    if (!str || !*str)
    {
        flag = 1;
        ft_putstr_fd("\n", fd);
        return;
    }

    while (str[i])
    {
        if (*str[i] == '-' && (ft_check_n(str[i]) == 0))
        {
            count++;
            i++;
            continue;
        }
          ft_putstr_fd(str[i], fd);

        if (str[i + 1])
            ft_putstr_fd(" ", fd);

        i++;
    }

    if (!count)
        ft_putstr_fd("\n", fd);
}


t_node  *ft_empty(void)
{
  t_node *head = NULL;
  char *pwd = getcwd(NULL, 0);
  insert_node (&head,pwd,"PWD");
  insert_node (&head,"1","SHLVL");
  insert_node (&head,"/usr/bin/env","_");
  return (head);
}
void ft_export (t_node ** env ,char ** args)
{
  if (args == NULL)
    ft_sort_env(env);
    puts("ok");
    print_list(*env);
  // else
  // {
  //   ft_parse_line (args);

  // }
}
void	do_builtin (t_minishell * minishell)
{
  if (ft_strncmp(minishell->list->cmd, "cd",2) == 0)
      ft_cd(minishell, convert_args(minishell->list->args));
  else if (ft_strncmp(minishell->list->cmd,"env",3)==0 && ft_lstsize(minishell->list->args) == 0)
    print_list( minishell->env);
  else if (ft_strncmp(minishell->list->cmd, "pwd",3) == 0)
    ft_pwd( minishell->env,"PWD");
  else if (ft_strncmp(minishell->list->cmd, "unset",5) == 0  && ft_lstsize(minishell->list->args) == 1)
    ft_unset(minishell->env,convert_args(minishell->list->args)[0]);
  else if (ft_strncmp(minishell->list->cmd, "echo",4) == 0)
    ft_echo (convert_args(minishell->list->args),STDOUT_FILENO);
  else if (ft_strncmp(minishell->list->cmd, "export",6) == 0)
    ft_export(&minishell->env,convert_args(minishell->list->args));
}
int is_builtin(t_minishell * minishell)
{
    if(ft_strncmp(minishell->list->cmd, "cd",3) == 0 || (ft_strncmp(minishell->list->cmd,"env",3)==0 && ft_lstsize(minishell->list->args) == 0)|| \
     ft_strncmp(minishell->list->cmd, "pwd",3) == 0||(ft_strncmp(minishell->list->cmd, "unset",5) == 0  && ft_lstsize(minishell->list->args))||(ft_strncmp(minishell->list->cmd, "echo",4) ==0) ||(ft_strncmp(minishell->list->cmd, "export",6) == 0))
      return (1);
    return (0);
}