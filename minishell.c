/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/05/28 04:58:56 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
 
#include"minishell.h"

int main (int ac,char **av,char** env)
{
    (void)ac;
    (void)av;
    char *line = NULL;
    char **t;
    t_parse_utils *p_prompt;
    
    ///CREATE PROMPT AND  ADD HISTORY
    while (1)
    {
        line = readline("minishell>>");
        // check_prompt(line);
        while (!line || !*line)
            line =readline("minishell>>");
        if (line && *line)
            add_history(line);//
        
        p_prompt = ft_calloc(1, sizeof(t_parse_utils));
        // char *p_clean = ft_strtrim(" echo \"hel | lo\" ", " ");
        // char *p_clean = ft_strtrim(" ls|grep x", " ");
        char *p_clean = ft_strtrim(line, " ");
        p_prompt->prompt = ft_strdup(p_clean);
        
        parse_prompt(p_prompt->prompt , p_prompt);
        
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
    //PRINT ENV
        if (strcmp(t[0],"cd")==0)
        {
            if (t[1] && *t[1])
                ft_cd(t[1]);
            else
                chdir(getenv("HOME"));
        }
        else if (strcmp(t[0],"env" )==0)
            ft_env(env);// in this function we put the env data in a linked list then we print it  
        else if (strcmp (t[0],"pwd")==0)
            ft_pwd();// in this function we create the builtin pwd
        //     echo(t);
    
    }
 
    //ENV part
}