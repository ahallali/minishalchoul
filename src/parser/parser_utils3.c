

#include "parser.h"


void print_lex(void *lex)
{
	t_lex *_lex;

	_lex = (t_lex *)lex;
	printf("TYPE : %d\n",_lex->type);
	printf("CMD  : %s\n",_lex->command_name);
	printf("VAR  : %s\n",_lex->variable);
	printf("FILE : %s\n",_lex->filename);
	printf("--------------\n");
}
void print_arg(void *arg)
{
	char *str;

	str = (char *)arg;
	printf("ARG : %s\n",str);
}
void print_exec(void *exec)
{
	t_exec_utils *_exec;

	_exec = (t_exec_utils *)exec;
	printf("CMD : %s\n",_exec->cmd);
	printf("INF : %s\n",_exec->infile);
	printf("OUT : %s\n",_exec->outfile);
	ft_lstiter(_exec->args, print_arg);
	printf("--------------\n");
}

// t_exec_utils *handle_exec()
// {

// }

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = -1;
	fd = access(filename, flags);
	if (fd < 0)
		perror("No such file or directory");
	return (fd);
}

t_list	*get_exec(t_parse_utils *u)
{
	t_lex			*tmp;
	t_list			*l_tmp;
	t_list			*result;
	t_exec_utils	*exec;
	int				fd[2];

	(void)fd;
	l_tmp = u->list_cmds;
	exec = ft_calloc(1, sizeof(t_exec_utils));
	result = NULL;
	while (l_tmp)
	{
		tmp = l_tmp->content;
		if (tmp->type == 1)
		{
			exec->cmd = tmp->command_name;
		}
		else if (tmp->type == 2)
		{
			ft_lstadd_back(&exec->args, ft_lstnew(tmp->variable));
		}
		else if (tmp->type == 5)
		{
			exec->infile = tmp->filename;
			if (tmp->filename)
				exec->inputFd = open_file(tmp->filename, tmp->flag);
			else
				exec->inputFd = tmp->fd;
		}
		else if (tmp->type == 6)
		{
			exec->outfile = tmp->filename;
			if (tmp->filename)
				exec->outputFd = open_file(tmp->filename, tmp->flag);
			else
				exec->outputFd = tmp->fd;
		}
		// printf("type : %d",tmp->type);
		// echo "hello" "world" | cat -e > out | ls <ifile < infile >ou >outfile | ls 'erezr'
		if (tmp->type == PIPE)
		{
			ft_lstadd_back(&result, ft_lstnew(exec));
			exec = ft_calloc(1, sizeof(t_exec_utils));
		}
		l_tmp = l_tmp->next;
	}
	ft_lstadd_back(&result, ft_lstnew(exec));
	return (result);
}

char **convert_args(t_list *node)
{
	int len;
	int tmp;
	char **result;
	t_list *n;


	len = ft_lstsize(node);
	result = NULL;
	tmp = 0;

	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	n = node;
	while (n)
	{
		result[tmp++] = ft_strdup((const char *)n->content);
		n = n->next;
	}
	return result;
}

char	**convert_command_args(t_exec_utils *utils)
{
	int		len;
	int		tmp;
	char	**result;
	t_list	*n;

	len = ft_lstsize(utils->args);
	result = NULL;
	tmp = 0;
	result = ft_calloc(len + 2, sizeof(char *));
	if (!result)
		return (NULL);
	result[tmp++] = utils->cmd;
	n = utils->args;
	while (n)
	{
		result[tmp++] = ft_strdup((const char *)n->content);
		n = n->next;
	}
	return (result);
}

char **convert_env(t_node  *node)
{
	char **exec_env;
	const char *joined;
	while (node)
	{
		joined = ft_strjoin(node->variable, ft_strjoin("=", ft_strjoin(node->value,"\n")));
		node = node->next;
	}
	exec_env = ft_split(joined, '\n');
	return (exec_env);
}