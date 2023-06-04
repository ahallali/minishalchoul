/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 04:52:03 by ahallali          #+#    #+#             */
/*   Updated: 2023/06/03 18:52:57 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_node * gt(char *str,t_node * head)
{
  t_node *new=head;
  char *t;
  char *oldpwd;

  oldpwd = getcwd(NULL, 0);
  if (chdir(str) == 0)
  {
	update_env(new,"OLDPWD",oldpwd);
	t =  getcwd(NULL,0);
	new =update_env(new,"PWD",t);
	// print_list(new);
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
	return (t);
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
  while (t->next)
  {
	if (!strcmp(t->variable, var))
		return (t->value);
	t = t->next;
  }
  puts("test");
  return (NULL);
}

t_node*  ft_cd (t_node* head,char ** t)
{
  t_node *new=NULL;
  char *tmp=NULL;
  if (t[1] && *t[1])
  {
	if (t[1][0]== '~')
	{
	  if (path_finder(head,"HOME"))
		tmp = path_finder(head,"HOME");
	  chdir(tmp);
	  update_env(head,"OLDPWD",path_finder(head,"PWD"));
	  new=update_env(head,"PWD",tmp);
	}
	if (t[1][0] == '-')
	{
		printf("%s",path_finder(head,"OLDPWD"));
	  if (path_finder(head,"OLDPWD")!= NULL)
	  {
		tmp = path_finder(head,"OLDPWD");    
	  chdir(tmp);
	  update_env(head,"OLDPWD",path_finder(head,"PWD"));
	  new=update_env(head,"PWD",tmp);
	  ft_pwd(new,"OLDPWD");
	  }
	  else
		perror("OLDPWD NOT SET");
	}
 	else if (!t[1] || !*t[1])
	{
	if (path_finder(head,"HOME"))
		tmp = path_finder(head,"HOME");
	if (chdir(tmp) == 0)
	{	
		update_env(head,"OLDPWD",path_finder(head,"PWD"));
	new=update_env(head,"PWD",tmp);
	}
	else
	new = gt(t[1], head);
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
	while (tmp != NULL) {
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}