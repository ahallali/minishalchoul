/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:26 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/23 16:41:00 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_info *validate_dquotes(char *str, int i)
{
    t_token_info *info;

    info = init_token_struct();
    if (str[i] == '"')
    {
        // puts("test\n");
        if (minishell->dquote_flag != '"')
        {
            printf("f added \n");
            minishell->dquote_flag = '"';
            i++;
        }
        if (minishell->dquote_flag == '"')
        {
            // printf("str[i - 1] : %c\n",str[i - 1]);
            while (str[i] && minishell->dquote_flag)
            {
                // puts("while\n");
                // printf("str[%d] : %c\n", i, str[i]);
                if (i > 0 && str[i] == '"' && str[i - 1] == '\\')
                    continue;
                else if (str[i] == '"')
                {
                    minishell->dquote_flag = '\0'; 
                    printf("f ended \n");
                }
                i++;
            }
            
            if (!str[i] && minishell->dquote_flag)
            {
                puts("here dq");
                info->word = str;
                info->limiter = NULL;
                info->next_start = str;
                return (info);
            }
            else if (!str[i])
            {
                info->word = str;
                info->limiter = NULL;
                info->next_start = NULL; 
                return (info);
            }
            else
            {
                printf("str : %s\n", str);
                printf("i : %d\n", i);
            }
            
            // if (i != 0 && str[i - 1] != '\\')
            // {
            //     minishell->dquote_flag = '\0'; 
            //     printf("f ended \n");
            //     i++;
            // }   
        }
    }
    return (NULL);
}