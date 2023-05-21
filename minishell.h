#ifndef MINISHELL_H
#define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
// void parse(char *line);
int ft_strlen(char *str);

char **ft_split(char  *s, char c);
void echo(char **str);
char *ft_substr(char *s, unsigned int start, size_t len);

int var_quote;

#endif
