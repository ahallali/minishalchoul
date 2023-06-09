/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:39:11 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/09 15:38:20 by ichaiq           ###   ########.fr       */
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
void   update_path(char * str , char * cmd,char **agrs,char ** env)
{
    if (!str || !cmd)
        return ;
    char ** tmp;
    char * path;
    tmp = NULL;
    tmp= ft_split(str,':');
    while (tmp && *tmp)
    {

    path = ft_strjoin(*tmp,ft_strjoin("/",cmd));
    // printf("path : %s\n", path);
    // printf("%s",*agrs);
    if (!access(path, X_OK))
        {
            pid_t pid;
            if((pid = fork()) == 0)
            {
                if (!execve(path,agrs,env))
                    printf("khdmat");
                
            }else waitpid(pid,NULL,0);
        }   
              
    tmp++;
    }
}