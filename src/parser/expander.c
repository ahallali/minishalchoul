/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/10 02:36:28 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *ft_str_replace(char *str, char *find, char *replace)
{
    size_t i;
    size_t y;
    size_t f_len;
    size_t t_len;
    char *result;

    i = 0;
    y = 0;
    f_len = ft_strlen(find);
    t_len = (ft_strlen(str) + ft_strlen(find) )+ ft_strlen(replace) + 100;
    result = ft_calloc(t_len+100000, sizeof(char));
    while (str[i])
    {
        if (ft_strncmp(&str[i], find, ft_strlen(find)) == 0)
        {
            i = i + ft_strlen(replace) ;            
            puts("rete");
            printf("result : %s\n",result);
            while (replace && *replace)
            {
                result[y++] = *replace;
                printf("a result : %s\n",result);
                replace++;
            }
        }
        else if(str[i] != '\0')
            result[y++] = str[i];
        i++;
    }
    return (result);
}

char *convert_path(char *str)
{
    int i;
    
    i = 0;
    
    if (i == 0 && str[i] == '$')
        i++;
    // printf("arg : %s\n",ft_strdup(&str[i]));
    return ft_strdup(&str[i]);

    
}


char *expand_dquotes(char *str, t_minishell *u)
{
    // "hello $LOGNAME, welcome"

    // (void)u;
    // char *env = path_finder(u->env,"HOME");
    int i;
    char *var;
    char *res;
    
    i = 0;
    res = str;
    while (str[i])
    {
        if (str[i] == '$')
        {
            var = ft_strtok(&str[i], " ", NULL);
            printf("var : %s\n",var);
            printf("str : %s\n",str);

            if (path_finder(u->env, convert_path(var))){

                    // printf("pf : %s\n",path_finder(u->env, convert_path(var)));
                res = ft_str_replace(res, var, path_finder(u->env, convert_path(var)));
                
            }
        }
        i++;
    }
    

    // char *res = ft_str_replace(str, "$HOME", "ichaiw");
    // printf("original str : %s\n",str);
    printf("result : %s\n",res);
    // printf("env HOME : %s\n",path_finder(u->env,"HOME"));
    return res;

}



