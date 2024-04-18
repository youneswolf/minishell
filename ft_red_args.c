#include "minishell.h"

int    ft_red_args_utils(t_line *tmp1, int flag)
{
    while (tmp1 && tmp1->token == CMD)
    {
        if (tmp1 && tmp1->token == CMD && flag == 1)
            tmp1->token = ARGS;
        tmp1 = tmp1->next;
    }
    return (0);
}

void    ft_red_args(t_line *head)
{
   t_line *tmp;
   t_line *tmp1;
   int  i;
   int  flag;

    tmp = head;
    while (tmp)
    {
        if (tmp->token == CMD)
            flag = 1;
        if (tmp->token == IN_REDIR || tmp->token == OUT_REDIR || tmp->token == APPEND)
        {
            tmp1 = tmp;
            if (tmp1->next->next)
                tmp1 = tmp1->next->next;
            else
                return ;
            flag = ft_red_args_utils(tmp1, flag);
        }
        tmp = tmp->next;
    }
}
