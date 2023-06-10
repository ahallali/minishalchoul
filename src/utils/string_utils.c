/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:12 by ichaiq            #+#    #+#             */
/*   Updated: 2023/06/10 01:15:08 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strStartWith(char *str, char c)
{
    return (str && *str == c);
}

int ft_strEndsWith(char *str, char c)
{
    return (str && str[ft_strlen(str) - 1] == c);
}