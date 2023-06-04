/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/03 18:50:24 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 
#include"minishell.h"

int main (int ac,char **av,char** env)
{
    (void)ac;
    (void)av;
    char *line = NULL;
    char **t;
    // t_parse_utils *p_prompt;
    t_node *head = NULL;
    t_node *new = NULL;

    if (*env)
    {  
    head = ft_env(env);
    }
    else 
    {
    // printf("EMPTY ENV \n");// to update
    }
    while (1)
    {
        line = readline("minishell>>");
        if (!line)
            exit(0);
        while (!line || !*line)
            line =readline("minishell>>");
        if (line && *line)
            add_history(line);//
        
        // p_prompt = ft_calloc(1, sizeof(t_parse_utils));
        // char *p_clean = ft_strtrim(" echo \"hel | lo\" ", " ");
        // char *p_clean = ft_strtrim(" ls|grep x", " ");
        // char *p_clean = ft_strtrim(line, " ");
        // p_prompt->prompt = ft_strdup(p_clean);
        
        // parse_prompt(p_prompt->prompt , p_prompt);
        
        // if (strcmp(line, "exit")==0)
        // {
        //     free (line);
        //     break;
        // }
        t =ft_split(line,' ');
        if (!t)
        {
            printf("error");
            return (0);
        }
        update_env(head,"OLDPWD",NULL);
        new=head;
    //CD && PWD && ENV BUILTIN DONE 
        if (strcmp(t[0],"cd")==0)
             ft_cd(new, t);
        else if (strcmp(t[0],"env")==0)
            print_list(new);
        else if (strcmp(t[0], "pwd") == 0)
            ft_pwd(new,"PWD");
        // else if (ft_strncmp(t[0], "export",6) == 0)
        //     ft_export(new,t[1]);
        // else if (ft_strncmp(t[0], "unset",6) == 0)
        //     ft_unset(new,t[1]);
    }
    
}