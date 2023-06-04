

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

void get_exec(t_parse_utils *u)
{
    t_lex *tmp;
    t_list *l_tmp;
    t_exec_utils *exec;
    int fd[2];

    (void)fd;
    l_tmp = u->list_cmds;
    exec = ft_calloc(1, sizeof(t_exec_utils));
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
            if (tmp->filename)
                exec->inputFd = open_file(tmp->filename, tmp->flag);
            else
                exec->inputFd = tmp->fd;
        }
        else if (tmp->type == 6)
        {
            if(tmp->filename)
                exec->outputFd = open_file(tmp->filename, tmp->flag);
            else
                exec->outputFd = tmp->fd;
        }
        l_tmp = l_tmp->next;

        // cat -e < minishell.c < outils.c | grep main > out1 out2

    }
    
}