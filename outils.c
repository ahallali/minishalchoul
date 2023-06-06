/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/06 01:18:04 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int ft_strlen (char *str)
// {
//     int i;
//     i =0;
//     while (str[i])
//     {
//         i++;
//     }
//     return (i);
//     }
// static size_t	wd(char *str, char sep)
// {
// 	size_t	i;
// 	size_t	count;
// 	int		flag;
// int ft_strlen (char *str)
// {
//     int i;
//     i =0;
//     while (str[i])
//     {
//         i++;
//     }
//     return (i);
//     }
// static size_t	wd(char *str, char sep)
// {
// 	size_t	i;
// 	size_t	count;
// 	int		flag;

// 	i = 0;
// 	count = 0;
// 	flag = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == sep)
// 			flag = 0;
// 		else if (flag == 0)
// 		{
// 			flag = 1;
// 			count += 1;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// static size_t	wl(char *str, char sep)
// {
// 	size_t	size;
// 	size_t	i;

// 	i = 0;
// 	size = 0;
// 	while (str[i] && str[i] != sep)
// 	{
// 		size++;
// 		i++;
// 	}
// 	return (size);
// }

// static char	**ft_free(char **ptr, int size)
// {
// 	while (--size >= 0)
// 	{
// 		free (ptr[size]);
// 		ptr[size] = NULL;
// 	}
// 	free(ptr);
// 	return (NULL);
// }

// static void	init_var(size_t	*i, size_t	*j, size_t	*size)
// {
// 	*i = 0;
// 	*j = 0;
// 	*size = 0;
// }

// char	**ft_split(char  *s, char c)
// {
// 	char	**ptr;
// 	size_t	j;
// 	size_t	i;
// 	size_t	size;

// 	if (!s)
// 		return (NULL);
// 	init_var(&i, &j, &size);
// 	ptr = (char **)malloc((wd((char *)s, c) + 1) * sizeof (char *));
// 	if (!ptr)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i] == '\0')
// 			break ;
// 		size = wl((char *)s + i, c);
// 		ptr[j] = ft_substr(s + i, 0, size);
// 		if (!ptr[j])
// 			return (ft_free(ptr, j));
// 		i += size;
// 		j++;
// 	}
// 	return (ptr[j] = NULL, ptr);
// }
// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	len_s;
// 	char	*ptr;

// // 	if (!s)
// // 		return (NULL);
// // 	len_s = ft_strlen(s);
// // 	i = 0;
// // 	if (start >= len_s)
// // 		len = 0;
// // 	else if (len > len_s)
// // 		len = len_s - start;
// // 	ptr = (char *)malloc(len + 1 * sizeof(char));
// // 	if (!ptr)
// // 		return (NULL);
// // 	while (i < len)
// // 	{
// // 		ptr[i] = s[start + i];
// // 			i++;
// // 	}
// // 	ptr[i] = '\0';
// // 	return (ptr);
// // }