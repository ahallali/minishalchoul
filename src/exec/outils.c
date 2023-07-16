/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/16 04:19:25 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_node *head, char *s)
{
	t_node	*t;
	char	*pwd;

	pwd = NULL;
	t = head;
		// puts("here");
	if (!head)
	{
		pwd = getcwd(NULL, 0);
		update_env(head, "PWD", pwd);
	}
	if (t)
	{
		while (t->next)
		{
			if (!strcmp(t->variable, s) && t->value)
			{
				ft_putstr_fd (t->value, 1);
				ft_putstr_fd ("\n", 1);
			}
			t = t->next;
		}
	}
}

void	print_list(t_node	*head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void del(char *str)
{
	if (str)
		free(str);
}

t_node	*ft_unset(t_node **head, char *var)
{
	t_node *t;
	t_node *tmp;

	t = *head;
	if (!head || !var)
		return (NULL);
	while (t)
	{
		if (!ft_strncmp(t->variable, var, ft_strlen(t->variable)) && ft_strncmp(t->variable, "_", 1))
		{
			if (t == *head)
			{
				*head = t->next;
				del(t->variable);
				del(t->value);
				free(t);
				t = *head;
			}
			else
			{
				tmp->next = t->next;
				del(t->variable);
				del(t->value);
				free(t);
				t = tmp->next;
			}
		}
		else
		{
			tmp = t;
			t = t->next;
		}
	}
	return (t);
}

void do_builtin(t_minishell *minishell)
{
	if (ft_strncmp(expand_dquotes(minishell->list->cmd), "cd", 2) == 0)
		ft_cd(minishell, convert_args(minishell->list->args));
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "env", 3) == 0 && ft_lstsize(minishell->list->args) == 0)
		print_list(minishell->env);
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "pwd", 3) == 0)
		ft_pwd(minishell->env, "PWD");
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "unset", 5) == 0 && ft_lstsize(minishell->list->args) == 1)
		ft_unset(&minishell->env, convert_args(minishell->list->args)[0]);
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "echo", 4) == 0)
		ft_echo(convert_args(minishell->list->args), STDOUT_FILENO);
	else if (ft_strncmp(expand_dquotes(minishell->list->cmd), "exit", 4) == 0)
		ft_exit(minishell, convert_args(minishell->list->args));
	else if (ft_strncmp(minishell->list->cmd, "export", 6) == 0)
	   ft_export(minishell, convert_args(minishell->list->args));
}

int end_key (char * str,char c)
{
	int i = 0;

	if (!str || !*str)
	   return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}


// char *key_value(char **arg, t_minishell *minishell)
// {
// 	// printf(" %/s | %s\n", arg[0], arg[1]);
// 	(void)minishell;
// 	// (void)arg;
// 	int i = -1;
// 	// int j = 0;
// 	// char	**res;
// 	int count = 0;
// 	char **tmp = arg;
// 	// char **keys;
		
	
// 	while (tmp[++i])
// 	{
// 		count++;
// 		// int x = check_key("^&a=") == 1;
// 		if (check_key(tmp[i]) == 1)
// 			return (fprintf(stdout, "Failure \n") , NULL);
// 	// n_export_and_env;
// 		int p = check_value(tmp[i]);
// 		if (p) //if the value exist
// 		{
// 			if (ft_strchr(tmp[i],'+'))
// 			{
// 			char *value = ft_substr(tmp[i], p+1,ft_strlen(tmp[i])); //the valid value to add
// 			char *key = ft_substr(tmp[i], 0, p-1);//the valid key to add
// 			printf("%s\n", key);
// 			printf("%s\n", value);
// 			add_to_export(minishell->export, key, value); // add to export linked list
// 			add_to_export(minishell->env,key,value);//add to env linked list
// 			}
// 		}
// 			// else 
// 			// add_to_export(minishell->export,key);
// 		// {

// 		// }
// 		// else 
// 		// 	check_valid_key(tmp[i]);
// 			// zid envrnmt;
// 			// zid export;
// 			// storekey(tmp[i]);
// 		// else
// 		// 	zid export;
// 		/*
// 			substr the key and store it in char **
// 			check_
// 		*/
// 	}
// 	return (0);
// }
// t_node *add_to_export(t_node *head,char *key ,char * value)
// {
// 	(void)minishell;
// 	t_node *tmp = head;
// 	if (!head)
// 		return NULL;
// 	while (tmp)
// 		{
// 			printf("%s\n",key);
// 			printf("%s\n",tmp->variable);
// 			if (ft_strncmp(key,tmp->variable,ft_strlen(key))==0)
// 			{
// 				puts("hna");
// 				tmp->value = ft_strjoin(tmp->value,value);
// 			}
// 			else
// 			{
// 				puts("hna2");
// 				insert_node(&head,value,key);
// 				break;
// 			}
// 			tmp=tmp->next;
// 		// }
// 		// {		
// 		// while (tmp)
// 		// {
// 		// 	if (!ft_strncmp(key,tmp->variable,ft_strlen(key)))
// 		// 		tmp->value = value;
// 		// 	else
// 		// 		insert_node(&head,value,key);
// 		// 	break;
// 		// tmp = tmp->next;
// 		// // else if (ft_strchr(arg[i], '=') != NULL && !arg[i - 1] == '+')
// 		// // {
// 		// // 	tmp = end_key(arg[i])
// 		// // }
// 		// // else if (check_key(arg[i]))

// 		// // i++;
// 		// }
// 		// else if (check_key(arg[i]))

// 		// i++;
// 	// }
// 	// print_list(minishell->export);
// 		}
// 	return (head);
// }
int check_key(char *str)
{
	int i = 1;
	int bk = 0;

	if (isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && (str[i] != '=') && str[i] != '+')
		{
			if (ft_isalnum(str[i]) || str[i] == '_')
				i++;
		}
		if (str[i] == '\0' || str[i] == '=' || (str[i] == '+' && str[i+1] == '='))
			bk = 1;
	}
	if (bk == 1)
		return (0); // succes
	return (1); // failure
}

int check_value(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i+1])
			return (i);
		i++;
	}
	return (0);
}

int check_valid_key(char*str)
{
	int i =0;
	while (str[i])
	{
		if (str[i] == '=' && !str[i + 1])
			return (i);
		i++;
	}
	return (0);
}
// char * key_value(char **arg,t_minishell * minishell)
// {
// 	(void)minishell;
// 	// int i = 0;
// 	char **tmp2 = arg;
// 	// int j;
// 	// int tmp = 0;
// 	// char *key;
// 	// int count = 0;
// 	// while (*tmp2++)
// 	// {
// 	// 	count++;
// 	// }
// 	printf("%d | %s | %s\n",count, arg[0], arg[1]);
// 	// while (i<count)
// 	// {
// 	//    	if (ft_strchr(arg[i],'=') != NULL && !arg[i+1])
// 	// 	{
// 	//    		tmp = end_key(arg[i], '=');
// 	// 		key = ft_substr(arg[i], 0, tmp+1);
// 	// 		if (!check_key(key))
// 	// 		printf("%s\n",key);
// 	// 		// insert_to_export(key,minishell);
// 	// 	}
// 	// 	// if (ft_strchr(arg[i],'+')!=NULL) 
// 	// 	// {
// 	// 	// 	if (arg[i] =='=')
// 	// 	// 		tmp = end_key(arg[i],'=');
// 	// 	// 	key = ft_substr(arg[i], 0, tmp - 2);
// 	// 	// }
// 	// 	i++;
// 	// }
// 	return (0);
// }
// void insert_new(char * key,t_minishell * minishell)
// {
// 	if (key)
// 	// update_env(minishell->export,)
// 	insert_node(&minishell->export,"\"\"",key);
// 	print_list(minishell->export);
// 	// else if ()
// }

// check_exist ()
// int check_operator(char **args)
// {
// 	int i =0;
// 	int j ;
// 	while (args[i])
// 	{
// 		j = 0;
// 		while (args[i][j])
// 		{
// 			if (args)		
// 		}
// 	}
// }



void ft_export(t_minishell *minishell, char **args)
{
	(void)minishell;
	int	x;
	
	x = 0;
	if (!args || !*args)
	   print_list(minishell->export);
	while (args && args[x])
		add_value(args[x++]);
		
	// else if (!key_value(args,minishell))
	   return;
}