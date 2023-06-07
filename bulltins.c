/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/06 22:33:08 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


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

void ft_echo(char **str,int fd)
{
  int i = 0;
  // int j = 0;
  int flag = 0;
  fd = STDOUT_FILENO;
  if (!str || !*str)
  {
        flag = 1;
        ft_putstr_fd("\n", fd);
  } 
    
  while (str && str[i])
  {
      if (i == 0 && *str[i] == '-' && (ft_check_n (str[0]) == 0))
      {
      // printf("%s", str[i+1]);
      ft_putstr_fd(str[i+1], fd);
      flag = 1;
      i++;
      if (str[i + 1])
        ft_putstr_fd(" ", fd);
      }
      else {
        
        ft_putstr_fd(str[i], fd);
        if (str[i+1])
          ft_putstr_fd(" ", fd);
      }

            // printf("%s",str[])
    i++;
  }
  if (!flag)
    ft_putstr_fd("\n", fd);
}
