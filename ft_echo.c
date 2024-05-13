#include "minishell.h"

#include "minishell.h"
void    ft_putnbr_fd(int n, int fd)
{
    long    num;
    int        i;
    char    a[10];

    num = n;
    if (num == 0)
        ft_putchar_fd('0', fd);
    if (num < 0)
    {
        ft_putchar_fd('-', fd);
        num = -num;
    }
    i = 0;
    while (num > 0)
    {
        a[i] = num % 10 + 48;
        num = num / 10;
        i++;
    }
    i--;
    while (i >= 0)
    {
        ft_putchar_fd(a[i], fd);
        i--;
    }
}

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

void echo_no_new_line(t_holder *holder, int *i, t_last *status)
{
    (*i)++;
    while (holder->args_built_in[*i + 1])
        {
            ft_put_str(holder->args_built_in[*i]);
            write(1, " ", 1);
            (*i)++;
        }
        if (holder->args_built_in[*i])
        {
            ft_put_str(holder->args_built_in[*i]);
        }
}

void    echo_new_line(t_holder *holder, int j, t_last *status)
{
    while (holder->args_built_in[j + 2])
        {
            ft_put_str(holder->args_built_in[j+ 1]);
            write(1, " ", 1);
            j++;
        }
        if (holder->args_built_in[j + 1])
        {
            ft_put_str(holder->args_built_in[j+ 1]);
        }
}

void exec_echo(t_holder *holder, t_last *status)
{
    int    i = 1;
    int    j = 0;
    if (!ft_strcmp_asd(holder->args_built_in[i], "-n"))
        echo_no_new_line(holder, &i, status);
    else
    {
        echo_new_line(holder, j, status);
        write(1, "\n", 1);
    }
}