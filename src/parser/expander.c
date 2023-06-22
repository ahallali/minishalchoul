/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/22 17:07:33 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
int count_occ(char *str, char *find)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (!ft_strncmp(find, &str[i], ft_strlen(find)))
        {
           count++;
           i += ft_strlen(find); 
        }
        else
            i++;
    }
    return (count);
}

int result_len(char *str, char *find, char *replace)
{
    int occ;
    occ = count_occ(str, find);
    return (ft_strlen(str) - (ft_strlen(find) * occ) + (ft_strlen(replace) * occ) ) + 1 ;
}

char *ft_str_replace(char *str, char *find, char *replace)
{
    size_t i;
    size_t y;
    size_t f_len;
    char *result;
    char *tmp;

    i = 0;
    y = 0;
    f_len = ft_strlen(find);
    tmp = replace;
    result = ft_calloc(result_len(str, find, replace) + 1, sizeof(char));
    while (str[i])
    {
        // printf("%zu | %s\n", i, &str[i]);
        if (ft_strncmp(&str[i], find, ft_strlen(find)) == 0)
        {
            i = i + ft_strlen(find);            
            replace = tmp;
            while (replace && (*replace != '\0'))
                result[y++] = *replace++;
        }
        else
            result[y++] = str[i++];

    }
    return (result);
}

char *convert_path(char *str)
{
    int i;
    
    i = 0;
    if (i == 0 && str[i] == '$')
        i++;
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
    char *tmp;
    // char *env_var;
    
    i = 0;
    res = str;
    // printf("str : %s\n",str);

    while (str[i])
    {
        // printf("str i : %c\n",str[i]);
        if (str[i] == '$')
        {
            tmp = ft_strdup(str);
            // var = ft_strtok(&tmp[i + 1], " $\"\0", NULL);
            var = extract_variable(&tmp[i]);
            // env_var = add_dollar_sign(var);
            printf("var : %s\n", var);
            // printf("env_var : %s\n", env_var);
            
            if (path_finder(u->env, convert_path(var + 1)))
                res = ft_str_replace(res, var, path_finder(minishell->env, convert_path(var + 1)));
            else 
                res = ft_str_replace(res, var, "");
            // i++;
        }
        i++;
    }
    

    // char *res = ft_str_replace(str, "$HOME", "ichaiw");
    printf("original str : %s\n",str);
    // printf("replace : %s\n",ft_str_replace("aaa $HOMEqsds as","$HOME","ismail_chaiq"));
    printf("result : %s\n",res);
    // printf("env HOME : %s\n",path_finder(u->env,"HOME"));
    return res;

}


