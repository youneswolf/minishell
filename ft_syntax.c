/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:47:58 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/05 17:52:24 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_syntax_quote(char *str)
{
    int i;
    int count;
    int flag;

    i = 0;
    count = 0;
    if (str[0] == '\''|| str[0] == '\"')
    {
        if (str[ft_strlen(str) - 1] == '\'' || str[ft_strlen(str) - 1] == '\"')
            flag = str[ft_strlen(str) - 1];
        flag = str[0];
    }
    while (str[i])
    {
        if (str[i] == flag)
            count++;
        i++;
    }
    if (count % 2 != 0)
    {
        write(2, "syntax error: double or single quote\n", 36);
        return (0);
    }
    return (1);
}

void    ft_syntax(t_line *head)
{
    int i;
    int flag;
    t_line  *tmp;
    int count;

    i = 0;
    count = 0;
    tmp = head;
    if (tmp && tmp->token == PIPE)
    {
        perror("parse error");
            return ;
    }
    while (tmp)
    {
        if (!ft_syntax_quote(tmp->str))
            return ;
        flag = tmp->token;
        if (tmp->next && flag == tmp->next->token && flag != ARGS)
        {
            perror("parse error");
            return ;
        }
        else if ((tmp->token == PIPE || tmp->token == HERDOC || tmp->token == IN_REDIR 
        || tmp->token == OUT_REDIR || tmp->token == APPEND) && !tmp->next)
        {
            perror("parse error");
            return ;
        }
        tmp = tmp->next;
    }
}
