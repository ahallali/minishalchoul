/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <ahallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/12 06:56:33 by ahallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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

void ft_pwd(t_node *head, char *s)
{
	t_node *t;
	char *pwd;

	pwd = NULL;
	t = head;
	if (!head)
	{
		pwd = getcwd(NULL, 0);
		update_env(head, "PWD", pwd);
	}
	if (!t)
	{
		while (t->next)
		{
			if (!strcmp(t->variable, s) && t->value)
			{
				printf("%s\n", t->value);
			}
			t = t->next;
		}
	}
	else
	{
		pwd = getcwd(NULL, 0);
		insert_node(&head, pwd, "PWD");
		printf("%s\n", pwd);
	}
}
void print_list(t_node *head)
{
	t_node *tmp;

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

t_node *ft_unset(t_node **head, char *var)
{
	t_node *t;
	t_node *tmp;

	t = *head;
	if (!head || !var)
		return (NULL);
	while (t)
	{
		if (!ft_strncmp(t->variable, var, ft_strlen(var)) && ft_strncmp(t->variable, "_", 1))
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
	// int count =0;
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
char * key_value(char **arg)
{
	int i = 0;
	// int j;
	int tmp = 0;
	char *key;
	// int count;
	while (arg[i])
	{
		// if (ft_strchr(arg[i],'+')!=NULL) 
		// {
		// 	if (arg[i] =='=')
		// 	puts("test");
		// 		tmp = end_key(arg[i],'=');
		// 	key = ft_substr(arg[i], 0, tmp - 2);
		// }
	   	if (ft_strchr(arg[i],'=') != NULL && !arg[i+1])
		{
			
	   		tmp = end_key(arg[i], '=');
			key = ft_substr(arg[i], 0, tmp+1);
			if (check_key(key))
			return (key);
		}
		else if (ft_strchr(arg[i], '=') != NULL && !arg[i - 1] == '+')
		{
			tmp = end_key(arg[i])
		}
		else if (check_key(arg[i]))

		i++;
	}
	return (key);
}

int check_key (char *str)
{
	int i = 1;
	int size = ft_strlen(str);
	if (isalpha(str[0])|| str[0] == '_')
	{
		while (i<size-1)
		{
			if (!ft_isalnum(str[i]))
				return(1);
			i++;
		}
	}
	return (0);
}

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
	
	if (!args || !*args)
	   print_list(minishell->export);
	else if (!key_value(args))
	   return;
}