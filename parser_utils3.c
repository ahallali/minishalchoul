

#include "minishell.h"


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
 
int open_file(char *filename,int flags)
{
    int fd;
    fd = -1;
    fd = open(filename, flags);
    if (fd < 0)
        perror("No such file or directory");
    return (fd);
}

t_list *get_exec(t_parse_utils *u)
{
    t_lex *tmp;
    t_list *l_tmp;
    t_list *result;
    t_exec_utils *exec;
    int fd[2];

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
            if(tmp->filename)
                exec->outputFd = open_file(tmp->filename, tmp->flag);
            else
                exec->outputFd = tmp->fd;
        }
        // printf("type : %d",tmp->type);
        // echo "hello" "world" | cat -e > out | ls <ifile < infile >ou >outfile | ls 'erezr'
        if (tmp->type == PIPE)
        {
            // if (pipe(fd))
		    //     perror("pipe error\n");

            ft_lstadd_back(&result, ft_lstnew(exec));
            exec = ft_calloc(1, sizeof(t_exec_utils));
            
        }
        l_tmp = l_tmp->next;
        // cat -e < minishell.c < outils.c | grep main > out1 out2

    }
    // if (!ft_lstsize(result))
    ft_lstadd_back(&result, ft_lstnew(exec));

    return (result);
}