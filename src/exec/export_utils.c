/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:30:53 by ichaiq            #+#    #+#             */
/*   Updated: 2023/07/18 21:49:17 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_tab(char **arr, int n)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (i < n - 1)
	{
		swapped = 0;
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

int	count_nodes(t_node *head)
{
	t_node	*tmp;
	int		count;

	tmp = head;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	fill_keys(char **keys, t_node *head)
{
	t_node	*node;
	int		i;

	node = head;
	i = 0;
	while (node)
	{
		keys[i++] = node->variable;
		node = node->next;
	}
}

void	print_export_list(void)
{
	char	**keys;
	t_node	*node;
	int		count;

	count = count_nodes(g_minishell->env);
	keys = ft_calloc (count + 1, sizeof(char *));
	if (!keys)
		return ;
	fill_keys(keys, g_minishell->export);
	while (keys && *keys)
	{
		node = get_node(g_minishell->export,*keys++);
		printf("delcare -x %s", node->variable);
		if (node->value)
			printf("=\"%s\"", node->value);
		printf("\n");
	}
}
