#include "minishell.h"

void    ft_put_str(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

void exec_echo(t_holder *holder)
{
    int i = 1;
    int    j = 0;
    if (!ft_strcmp_asd(holder->args_built_in[i], "-n"))
    {
        i++;
        while (holder->args_built_in[i + 1])
        {
            ft_put_str(holder->args_built_in[i]);
            write(1, " ", 1);
            i++;
        }
        if (holder->args_built_in[i])
        {
            if (i > 2)
                write(1, " ", 1);
            ft_put_str(holder->args_built_in[i]);
        }
    }
    else
    {
        while (holder->args_built_in[j + 2])
        {
            ft_put_str(holder->args_built_in[j + 1]);
            write(1, " ", 1);
            j++;
        }
        if (holder->args_built_in[j + 1])
        {
            if (i > 2)
                write(1, " ", 1);
            ft_put_str(holder->args_built_in[j + 1]);
        }
        write(1, "\n", 1);
    }
}