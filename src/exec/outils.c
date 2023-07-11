/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:20:13 by ahallali          #+#    #+#             */
/*   Updated: 2023/07/11 00:36:45 by ahallali         ###   ########.fr       */
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

void	ft_pwd(t_node *head, char *s)
{
	t_node	*t;
	char	*pwd;

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
			if (!strcmp(t->variable, s) && t->value )
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
		printf("%s\n",pwd);
	}
}
void	print_list(t_node *head)
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

void	del(char  *str)
{
	if (str)
		free(str);
}

t_node	*ft_unset(t_node **head, char *var)
{
	t_node	*t;
	t_node	*tmp;

	t = *head;
	if (!head || !var)
		return (NULL);
	while (t)
	{
		if (!ft_strncmp(t->variable, var, ft_strlen(var)) \
			&& ft_strncmp(t->variable, "_", 1))
		{
			if (t==*head)
			{
				*head = t->next;
				del(t->variable);
				del(t->value);
				free(t);
				t=*head;
			}
			else 
			{
				tmp->next = t->next;
				del(t->variable);
				del(t->value);
				free(t);
				t=tmp->next;
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

void	do_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->list->cmd, "cd", 2) == 0)
		ft_cd(minishell, convert_args(minishell->list->args));
	else if (ft_strncmp(minishell->list->cmd, "env", 3) == 0 \
		&& ft_lstsize(minishell->list->args) == 0)
		print_list(minishell->env);
	else if (ft_strncmp(minishell->list->cmd, "pwd", 3) == 0)
		ft_pwd(minishell->env, "PWD");
	else if (ft_strncmp(minishell->list->cmd, "unset", 5) == 0 \
		&& ft_lstsize(minishell->list->args) == 1)
		ft_unset(&minishell->env, convert_args(minishell->list->args)[0]);
	else if (ft_strncmp(minishell->list->cmd, "echo", 4) == 0)
		ft_echo(convert_args(minishell->list->args), STDOUT_FILENO);
	else if (ft_strncmp(minishell->list->cmd, "exit", 4) == 0)
	{
		ft_exit(minishell, convert_args(minishell->list->args));
	}
}

	// else if (ft_strncmp(minishell->list->cmd, "export", 6) == 0)
	//    ft_export(&minishell->env, convert_args(minishell->list->args));
