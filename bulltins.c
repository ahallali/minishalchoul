/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/05/22 02:06:00 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void print_list(t_node* head) {
    t_node* tmp = head;
    while (tmp != NULL) {
        printf("%s=%s\n", tmp->variable, tmp->value);
        tmp = tmp->next;
    }
}
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


void echo (char **str)
{
  int i = 1;
  int j = 0;
  if (!str[i] || *str[i] == '\0')
    printf("\n");
  while (str[i])
  {
    if (str[i][j] == '-')
    {
      j++;
      if (!check_n_arg(str[i]))
        {
        i++;
        printf("%s ",str[i]);
        }
      // if (str[i][j] == '\'' || str[i][j] == '\"')
      // {
      //   j++;
      //   printf("%s", str[i]);
      //   printf(" ");
      // }
    }
    // else
    //   if (str[i][j] == '\"' || str[i][j] == '\'')
    //   {      
    //   i++;
    //   printf("%s ",str[i]);
    //   }
    i++;
  }
}

