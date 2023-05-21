/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulltins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:38:45 by ahallali          #+#    #+#             */
/*   Updated: 2023/05/21 20:48:18 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void check_n_arg(char *str)
{
  int i = 1;
  
  while (str[i])
  {
    if (str[i] != 'n')
      {
      // printf("-%c ",str[i]);
    // else{
    }
    i++;
  }
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
      check_n_arg(str[1]);
      // if (str[i][j] == '\'' || str[i][j] == '\"')
      // {
      //   j++;
      //   printf("%s", str[i]);
      //   printf(" ");
      // }
    }
    else
      printf("%s\n",str[i]);
    i++;
  }
}