/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:32:14 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/12 18:14:46 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int count_occurrences(char *str, char *find) {
    int count = 0;
    char *temp = str;

    while ((temp = strstr(temp, find)) != NULL) {
        count++;
        temp += strlen(find);
    }

    return count;
}

void perform_replacements(char *result, char *str, char *find, char *replace) {
    while (*str) {
        if (strstr(str, find) == str) {
            strcpy(result, replace);
            result += strlen(replace);
            str += strlen(find);
        } else {
            *result++ = *str++;
        }
    }
    *result = '\0'; // Add null terminator to the end of the result string
}

int calculate_result_length(char *str, char *find, char *replace, int find_len, int replace_len, int count) {
    int str_len = strlen(str);
    replace_len = ft_strlen(replace);
    find_len = ft_strlen(find);
    return str_len + count * (replace_len - find_len);
}

// char *str_replace(char *str, char *find, char *replace) {
//     char *result; // Pointer to the result string
//     char *temp; // Pointer to temporarily store portions of the original string
//     int find_len = strlen(find);
//     int replace_len = strlen(replace);
//     int count = 0;
    
//     // Count the occurrences of 'find' in 'str'
//     temp = str;
//     while ((temp = strstr(temp, find)) != NULL) {
//         count++;
//         temp += find_len;
//     }
    
//     // Allocate memory for the result string with enough space
//     // to accommodate the replacements
//     result = (char *) malloc(strlen(str) + count * (replace_len - find_len) + 1);
//     if (result == NULL) {
//         return NULL; // Memory allocation failed
//     }
    
//     temp = result;
    
//     // Iterate through 'str' and replace occurrences of 'find' with 'replace'
//     while (*str) {
//         if (strstr(str, find) == str) { // If 'find' is found at the current position
//             strcpy(temp, replace); // Replace 'find' with 'replace' in 'result'
//             temp += replace_len;
//             str += find_len;
//         } else {
//             *temp++ = *str++;
//         }
//     }
//     *temp = '\0'; // Add null terminator to the end of the result string
    
//     return result;
// }
char *str_replace(char *str, char *find, char *replace) {
    int find_len = strlen(find);
    int replace_len = strlen(replace);
    int count = count_occurrences(str, find);
    int result_len = calculate_result_length(str, find, replace, find_len, replace_len, count);

    char *result = (char *) malloc(result_len + 1);
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    perform_replacements(result, str, find, replace);

    return result;
}

char *ft_str_replace(char *str, char *find, char *replace)
{
    size_t i;
    size_t y;
    size_t f_len;
    size_t t_len;
    char *result;

    i = 0;
    y = 0;
    printf("str : %s\n",str);
    f_len = ft_strlen(find);
    t_len = (ft_strlen(str) - ft_strlen(find) )+ ft_strlen(replace) + 1;
    printf("t_len : %zu\n",t_len);
    result = ft_calloc(t_len + 1, sizeof(char));
    while (y < t_len)
    {
        printf("i : %zu\n",i);
        if (i < t_len && ft_strncmp(&str[i], find, ft_strlen(find)) == 0)
        {
            i = i + ft_strlen(find) ;            
            // puts("rete");
            // printf("result : %s\n", result);
            while (replace && (*replace != '\0'))
            {
                result[y++] = *replace++;
                printf("a result : %s\n", result);
            }
            // puts("te");
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
    char *tmp;
    
    i = 0;
    res = str;
    printf("str : %s\n",str);

    while (str[i])
    {
        printf("str i : %c\n",str[i]);
        if (str[i] == '$')
        {
            tmp = ft_strdup(str);
            var = ft_strtok(&tmp[i], " \"\0", NULL);
            printf("var : %s\n",var);
            
            if (path_finder(u->env, convert_path(var)))
                res = ft_str_replace(str, var, path_finder(minishell->env, convert_path(var)));
            else 
                res = ft_str_replace(str, var, "");
            i++;
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


