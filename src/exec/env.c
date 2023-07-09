/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaiq <ichaiq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:06:09 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/08 23:09:11 by ichaiq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_node *create_node(char *value,char *variable)
{
  	t_node	*new = ft_calloc (1, sizeof(t_node));
  	if (!new)
		return (NULL);
	new->value=strdup(value);
	new->variable = strdup(variable);
	new->next = NULL;
	return (new);
}
void  insert_node(t_node **head,char *value,char *variable)
{
 	t_node *new=create_node(value,variable);
  	t_node *current;
  	if (*head == NULL)
    	*head=new;
	else
	{
 		current= *head;
	
  		while (current->next != NULL)
  		{
    		current=current->next;
  		}
  		current->next = new;
	}
}
t_node * ft_env(char **env)
{
  	t_node *head = NULL;
	while (*env)
	{
		char* tmp =strchr(*env,'=');
		if (tmp!=NULL)
			*tmp='\0';
		char *value = tmp+1;
		char *variable = *env; 
		insert_node(&head,value,variable);
		env++;
	}
	return (head);
}
void swap_nodes(t_node **head , t_node  *n,t_node *m)
{
	if (n==m || !n || !m )
		return ;
	t_node *pre_n=NULL;
	t_node *pre_m=NULL;
	t_node *current=*head;
	while (current && (pre_n != NULL || pre_m != NULL))
	{
		if (current->next == n)
			pre_n=current;
		else if (current->next == m)
			pre_m = current;
		current = current->next;
	}
	if (pre_n == NULL || pre_m == NULL)
		return;
	if (pre_n!= NULL)
		current->next = pre_m;
	else 
		*head = m;
	if (pre_m!= NULL)
		current->next = pre_n;
	else
		*head = n;
	struct s_node *tmp = n->next;
	n->next=m->next;
	m->next = tmp;
}
void ft_sort_env(t_node** env)
{
}
