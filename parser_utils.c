/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 23:33:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/05/26 01:25:26 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* ft_strtok(char* str, const char* delimiters) {
    static char* token;  
    static char* lastToken;  

    if (str != NULL)
        token = str;
    else if (token == NULL)
        return NULL;

    lastToken = token;

    if (*lastToken == '\0')  // Reached the end of the string
        return NULL;

    // Find the start of the next token
    while (*token != '\0') {
        const char* delimiter = delimiters;
        while (*delimiter != '\0') {
            if (*token == *delimiter) {
                *token = '\0';  // Replace delimiter with null character
                token++;
                return lastToken;
            }
            delimiter++;
        }
        token++;
    }

    return lastToken;
}
void parse_prompt(char *p)
{
    (void)p;
    printf("parser : %s\n", ft_strtok("qsdqsdqsd| fsdfsdf|sqsd","|"));
    
}

// int main()
// {
// }