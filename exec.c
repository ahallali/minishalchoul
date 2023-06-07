/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:39:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/07 01:58:51 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

int ft_check_n(char * str)
{
    int i = 1;
    if (!str || !*str)
        return(1);
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
    
}
char *    update_path(char * str , char * cmd,char **agrs,char ** env)
{
    if (!str || !cmd)
        return (NULL);
    char ** tmp;
    char * path;
    tmp = NULL;
    tmp= ft_split(str,':');
    while (tmp && *tmp)
    {

    path = ft_strjoin(*tmp,ft_strjoin("/",cmd));
    printf("path : %s\n", path);
    if (!access(path, X_OK))
        {
            if (execve(str,agrs,env))
                printf("khdmat");
        }
            else
              perror("not found");
    tmp++;
    }

    return (path);
}