/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/08 20:05:28 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node * gt(char *str,t_node * head)
{
  t_node *new=head;
  char *t;
  char *oldpwd;

  oldpwd = getcwd(NULL, 0);
  if (chdir(str) == 0)
  {
	update_env(head,"OLDPWD",oldpwd);
	t =  getcwd(NULL,0);
	new=update_env(head,"PWD",t);
	return (new);
  }
  else
  {
	perror(str);
	return(NULL);
  }
} 

t_node * update_env(t_node *head ,char *var,char * data)
{
	t_node * t;
	t = head;
	while (t->next)
	{
		if (!strcmp(t->variable, var))
			t->value = data;
		t=t->next;
	}
	return (head);
}
// t_node *envi(char ** str)
// {
  
// }
// t_node * sort_var(t_node * head,char * s)
// {
//   t_node *t = head;
//   t_node *l = NULL ;
  
//   int swapped=0;
//   s = NULL;
//   if (!head)
//     return (NULL);
//   while (swapped)
//   {
//     while (t->next != l)
//     {
//     swapped = 0;
//     if (strcmp((char *)t->variable,(char *)t->next->variable)>0)
//     {
//       char *vartmp = t->variable;
//       char *valtmp = t->value;

//       t->variable = t->next->variable;
//       t->value = t->next->value;

//       t->next->variable = vartmp;
//       t->next->value = valtmp;
//       swapped = 1;
//     }
//     t = t->next;
//     }
//     l = t;
//     // t = head;
//   }
//   return (head);
// }

// t_node *ft_export(t_node *head,char *s)
// {
//   t_node *new;
//   new =sort_var(head, s);
//   print_list (new);
//  return (head);
// }

char * path_finder(t_node *head ,char *var)
{
  t_node * t;
  t = head;
  if (!head)
	return (NULL);
  while (t->next)
  {
	if (!strcmp(t->variable, var))
		return (t->value);
	t = t->next;
  }
  return (NULL);
}

t_node*  ft_cd (t_minishell *head, char ** t)
{
  t_node *new=NULL;
  char *tmp=NULL;
 

	
  	if (t[0] && *t[0])
  	{
		if (t[0][0] == '~')
		{
			if (path_finder(head->env,"HOME"))
				tmp = path_finder(head->env,"HOME");
			if (chdir(tmp)==0)
				return (NULL);
			else 
			{
			head->env = update_env(head->env, "OLDPWD", path_finder(head->env, "PWD"));
			head->env =update_env(head->env,"PWD",tmp);
			}
		}
		else
			new = gt(t[0], head->env);
	}
	else if (!t[0] || !*t[0])
	{
		if (path_finder(head->env,"HOME"))
			tmp = path_finder(head->env,"HOME");
		if (chdir(tmp) == 0)
		{	
			update_env(head->env,"OLDPWD",path_finder(head->env,"PWD"));
			new=update_env(head->env,"PWD",tmp);
		}
	}
	return (new);
}
void ft_pwd(t_node *head,char *s)
{
  t_node * t;
  t = head;
  while (t->next)
  {
	if (!strcmp(t->variable, s))
		printf("%s\n", t->value);
	t = t->next;
  }
}

void print_list(t_node* head) {
	t_node* tmp = head;
	while (tmp != NULL) 
	{
		if (!tmp->value)
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}
void del (void *ptr)
{
	(void)ptr;
}
t_node * ft_unset(t_node * head,char * var)
{
	t_node * t=head;
	t_node *tmp;
	
	if (!head || !var)
		return (NULL);
	while (t)
	{
		if (!strcmp(t->variable,var) && strcmp(t->variable,"_"))
		{
		del(t->variable);
		tmp->next = t->next;
		}
		tmp = t;
		t = t->next;
	}
	return (t);
}
