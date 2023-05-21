/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:56:47 by ahallali          #+#    #+#             */
/*   Updated: 2023/05/21 20:34:13 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
int main ()
{
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
            if (strcmp (t[0],"echo") == 0)
                echo(t);
    }
}