/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquotes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:26 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/23 20:26:27 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *get_new_line(char *prompt, t_parse_utils *utils, char c)
{
	char	*line;
	char	*tmp;

	(void)utils;
	tmp = readline(prompt);
	// if (!tmp)
	//     return (tmp);
	if (!ft_strchr(tmp, c))
	{
		line = ft_strjoin(tmp, "\n"); 
		free(tmp);
	}
	else
		line = tmp;
	return (line);   
}

void parse_quotes(t_token_info *tok, t_parse_utils *utils)
{
	int		i;
	char	c;
	char	*line;

	i = 1;
	while ((*tok->next_start == '"' || *tok->next_start == '\'')
		&& ft_strlen(tok->next_start) >= 1)
	{
		c = *tok->next_start;
		while (tok->next_start[i] && tok->next_start[i] != c)
			i++;
		if (tok->next_start[i] && tok->next_start[i] == c)
		{
			insert_to_lexer(ft_substr(tok->next_start, 0, ++i), utils);
			tok->next_start = &tok->next_start[i];
			break ;
		}
		else
		{
			if (!utils->wait_dquote || minishell->dquote_flag != '\0')
				tok->next_start = ft_strjoin(tok->next_start, "\n");
			utils->wait_dquote = 1;
			line = get_new_line(">", utils, c);
			tok->next_start = ft_strjoin(tok->next_start, line);
		}
	}
}


t_token_info *validate_dquotes(char *str, int *i)
{
    t_token_info *info;

    info = init_token_struct();
    if (str[*i] == '"')
    {
        // puts("test\n");
        if (minishell->dquote_flag != '"')
        {
            printf("f added \n");
            minishell->dquote_flag = '"';
            (*i)++;
        }
        if (minishell->dquote_flag == '"')
        {
            // printf("str[i - 1] : %c\n",str[i - 1]);
            while (str[*i] || (minishell->dquote_flag && str[*i]))
            {
                // puts("while\n");
                printf("str[%d] : %c\n", *i, str[*i]);
                if (i > 0 && str[*i] == '"' && str[*i - 1] == '\\')
                    continue;
                else if ( minishell->dquote_flag == str[*i]
                // && (ft_strnchr(_DELIMS_PARSE,str[*i + 1], 5)
                // || ft_strnchr("\"'", str[*i + 1],2))
                // )
                )
                {
                    minishell->dquote_flag = '\0'; 
                    printf("f ended \n");
                    break ;
                    // printf("X str[%d] : %c\n", *i, str[*i]);
                    // // (*i)++;
                    // printf("X str[%d] : %c\n", *i, str[*i]);
                }
                (*i)++;
            }
            
            // if (!str[*i] && minishell->dquote_flag)
            // {
            //     puts("here dq");
            //     info->word = str;
            //     info->limiter = NULL;
            //     info->next_start = str;
            //     return (info);
            // }
            if (!str[*i] && !minishell->dquote_flag)
            {
                info->word = str;
                info->limiter = NULL;
                info->next_start = NULL; 
                return (info);
            }
            else if (minishell->dquote_flag != 0)
            {
                info->next_start = NULL;
                return (info);
            }
            else
            {
                printf("str : %s\n", str);
                printf("i : %d\n", *i);
                // info->word = str;
                // info->limiter = NULL;
                // info->next_start = NULL; 
                // return (info);
            }
            
            // if (i != 0 && str[i - 1] != '\\')
            // {
            //     minishell->dquote_flag = '\0'; 
            //     printf("f ended \n");
            //     i++;
            // }   
        }
    }
    return (NULL);
}