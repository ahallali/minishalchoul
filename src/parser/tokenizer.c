/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 03:30:54 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/08 15:39:33 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_token_info *next_word(char *str, char *delimiter)
{
	t_token_info *info;
	int i;
	char *c;

	if (!str)
		return (NULL);
	info = ft_calloc(1, sizeof(t_token_info));
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(QUOTES_PARSE, str[i]))
			skip_quoted(str, &i);
		// REDIRECTIONS
		if (str[i] && (c = ft_strchr(IO_PARSE, str[i]) ) != 0)
		{
			
			info->word = ft_substr(str, 0, i);
			if ((ft_strnchr(IO_PARSE, str[i + 1], 1) && ft_strnchr(IO_PARSE, str[i + 2], 1)
				)|| (str[i] == IO_PARSE[1] && str[i + 1] == IO_PARSE[0]))
				return (perror("Syntax error : unexpected token found"),NULL);
			while (str[i + 1] == *c && !ft_strchr("<>", *c))
				i++;
			if (str[i] == str[i + 1])
				info->limiter = ft_substr(str, i++, 2);
		
			else {
				info->limiter = &str[i];
				info->word = ft_substr(str, 0, i);
			}
			info->next_start = &str[i + 1];
			return info;
		}
		// TOKEN DELIMITER
		if (str[i] && (c = ft_strchr(delimiter, str[i]) ))
		{
			// puts("delimiter found\n");
			info->word = ft_substr(str, 0, i);
			// if (str[i] == *delimiter && str[i + 1] == *delimiter)
			// printf("str[i] : %c\n",str[i]);
			// printf("str[i + 1] : %c\n",str[i + 1]);
			// printf("delimiter : %c\n",*delimiter);
			if (ft_strnchr(DELIMS_PARSE, str[i], 2) && ft_strnchr(DELIMS_PARSE, str[i + 1],1))
				return (perror("Syntax error : unexpected token found2"),NULL);
			info->limiter = &str[i];
			info->next_start = &str[i + 1];
			return info;
		}
		if (str[i])
			i++;
		if (!str[i])
		{
			info->word = str;
			info->limiter = NULL;
			info->next_start = NULL;
			return info;
		}
		// if (ft_strStartWith(info->word, '"') && !ft_strEndsWith(info->word, '\''))
		// while (/* condition */)
		// {
		//     /* code */
		// }
		
	}
	return NULL;
}

t_lex   *init_lexer_struct()
{
	t_lex   *lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		return (lex);
	lex->fd = -1;
	return (lex);
}

int insert_to_lexer(char *str, t_parse_utils *u)
{
	t_list *node;
	t_lex *lex;
	t_lex *last_lex;

	lex = ft_calloc(1, sizeof(t_lex));
	if (ft_strchr(IO_PARSE, *str))
		return (token_redirection (str, lex, last_lex, u));
	
	node = u->list_cmds;
	if (!node)
	{
		lex->type = CMD;
		lex->command_name = str;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	node = ft_lstlast(u->list_cmds);
	last_lex = (t_lex *)node->content;
	if (*str == '|')
	{
		lex->type = PIPE;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);

	}
	
	else if (last_lex->type == REDIRECTION_OUTPUT && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_outfile = O_CREAT | O_TRUNC | O_WRONLY;
		// lex->variable = str;
		// ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	else if (last_lex->type == REDIRECTION_AOUTPUT && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->outfiles, ft_lstnew(str));
		last_lex->flag_outfile = O_CREAT | O_APPEND | O_WRONLY;
		return (1);
	}
	else if (last_lex->type == REDIRECTION_INPUT  && !last_lex->filename)
	{
		last_lex->filename = str;
		ft_lstadd_back(&last_lex->infiles, ft_lstnew(str));
		last_lex->flag_infile = O_RDONLY;
		return (1);
	}
	else if (is_enum_redirection(last_lex->type) && last_lex->command_name == NULL)
	{
		lex->type = CMD;
		lex->command_name = str;
		last_lex->command_name = str;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);
	}
	else if (last_lex->type != PIPE && last_lex != lex)
	{
		lex->type = ARG;
		// lex->last
		lex->variable = str;
		lex->command_name = last_lex->command_name;
		ft_lstadd_back(&u->list_cmds, ft_lstnew(lex));
		return (1);

	}
	else if (last_lex->type == PIPE || (last_lex->type != ARG && last_lex->type != CMD))
	{
		lex->type = CMD;
		lex->command_name = str;
		node = ft_lstnew(lex);
		ft_lstadd_back(&u->list_cmds, node);
		return (1);
	}
	return (0);
}