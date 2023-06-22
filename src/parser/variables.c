/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:28:58 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/22 17:13:21 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

int is_valid_variable(char *var)
{
    int i;

    i = 0;
    if (!var[i] || var[i] != '$' || !ft_isdigit(var[++i]))
        return (0);
    while (ft_isalpha(var[i]) || var[i] == 95 || ft_isdigit(var[i]))
        i++;
    if (!var[i])
        return (1);
    return (0);
}

char *add_dollar_sign(char *var)
{
    int len;
    char *res;
    char *tmp;

    len = ft_strlen(var) + 2;
    res = ft_calloc(len, sizeof(char));
    tmp = res;
    if (!tmp)
        return (tmp);
    *tmp++ = '$';
    while (var && *var)
        *tmp++ = *var++;
    return (res);
}

char *extract_variable(char *str)
{
    int     i;
    char    *tmp;
    
    i = 0;
    // tmp = NULL;
    if (!str || !*str || *str != '$')
        return (NULL);
    if (ft_isdigit(str[++i]))
    {
        tmp  = ft_substr(str, 0, i + 1);
        printf("tmp 1 : %s\n",tmp);
        return (tmp);
    }
    while (!ft_strchr(" $\"\0", str[i]))
        i++;
    tmp = ft_substr(str, 0, i);
    printf("tmp 2 : %s\n",tmp);
    return (tmp);
}