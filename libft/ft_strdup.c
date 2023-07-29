/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:19:59 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/29 21:16:01 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		len;
	
	// printf("%s", s1);
	len = ft_strlen((const char *)s1);
	new = ft_calloc((len + 1), sizeof(char));
	if (!new)
		return (NULL);
	if (len == 0)
	{
		*new = '\0';
		return (new);
	}
	while (*s1)
		*new++ = *s1++;
	*new = '\0';
	return (new - len);
}
