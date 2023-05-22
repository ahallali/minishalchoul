/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/05/22 02:04:33 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int main (int ac,char **av,char** env)
{
    (void)ac;
    (void)av;
    char *line = NULL;
    char **t;
    while (1)
    {
        line = readline("minishell>>");
        while (!line || !*line)
            line =readline("minishell>>");
        if (strcmp(line, "exit")==0)
        {
            free (line);
            break;
        }
    // parse(line)l;
    t =ft_split(line,' ');
    if (!t)
        {
            printf("error");
            return (0);
        }
        // if (strcmp (t[0],"echo") == 0)
        //     echo(t);
    //PRINT ENV
    
    if (strcmp(t[0],"env" )==0)
        ft_env(env);// in this function we put the env data in a linked list then we print it  
    }
    // StORE ENV IN A LINKED LIST
   
 
    //ENV part
}