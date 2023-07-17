/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcollector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:06:45 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/17 17:27:10 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_gcollector(void)
{
	static t_list	**gcollector;

	if (!gcollector)
	{
		gcollector = malloc(1 * sizeof(t_list *));
		ft_bzero(gcollector, sizeof(t_list *));
	}
	return (gcollector);
}

void	set_gcollector(t_list *gcol)
{
	t_list	**gcollector;

	gcollector = get_gcollector();
	*gcollector = gcol;
}

void	add_gcol(void *ptr)
{
	t_list	*node;
	t_list	**gcol;
	t_list	*tmp;

	gcol = get_gcollector();
	node = malloc(sizeof(t_list));
	node->content = ptr;
	node->next = NULL;
	tmp = *gcol;
	if (!tmp)
		return (set_gcollector(node));
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	ft_free(void *ptr)
{
	t_list	*last;
	t_list	**gcol;
	t_list	*tmp;
	t_list	*first;

	gcol = get_gcollector();
	first = *gcol;
	last = *gcol;
	tmp = *gcol;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (last && last != first)
				last->next = tmp->next;
			else if (first == last)
				first = tmp->next;
			free(tmp->content);
			free(tmp);
			set_gcollector(first);
			break ;
		}
		else
			tmp = tmp->next;
	}
}
