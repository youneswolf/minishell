/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:47:58 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/20 15:06:47 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int    ft_syntax_quote(char *str, int i, int count)
{
    int flag;

    while (str && str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            flag = str[i];
            (1) && (count++,  i++);
            while (str[i])
            {
                if (str[i] == flag)
                {
                    (1) && (count++,  flag = 0);
                    break;
                }
                i++;
            }
        }
        if (str[i])
            i++;
    }
    if (count % 2 != 0)
        return (printf("syntax error: double or single quote\n"), 0);
    return (1);
}
int     ft_her_doc(t_line *head)
{
    t_line *tmp;

    tmp = head;
    while (tmp && tmp->next)
    {
        if (tmp->token == HERDOC && tmp->next->token == HERDOC)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

int    ft_syntax(t_line *head)
{
    int i;
    int flag;
    t_line  *tmp;
    int count;

    i = 0;
    count = 0;
    tmp = head;
    if (!tmp)
        return (0);
    if (tmp && tmp->token == PIPE || ft_her_doc(head) || (tmp->token == IN_REDIR && !tmp->next) || (tmp->token == HERDOC && !tmp->next))  
        return (head->status->status = 255, printf("error near2 `%s'\n", tmp->str), 0);
    while (tmp)
    {
        if (!ft_syntax_quote(tmp->str, i, count))
            return (0);
        flag = tmp->token;
        if (tmp->next && flag == tmp->next->token && flag != ARGS)
            return (head->status->status = 255, printf("error near `%s'\n", tmp->str), 0);
        else if (tmp->next && (tmp->token == IN_REDIR || tmp->token == OUT_REDIR) && tmp->next->token == PIPE)
            return (head->status->status = 255, printf("error near2 `%s'\n", tmp->str), 0);
        else if (tmp->next && tmp->token ==HERDOC && tmp->next->token == PIPE)
            return (head->status->status = 255, printf("error near2 `%s'\n", tmp->str), 0);
        else if (tmp->next && tmp->token == PIPE && (tmp->next->token == IN_REDIR || tmp->next->token == OUT_REDIR))
            return (head->status->status = 255, printf("error near2 `%s'\n", tmp->str), 0);
        else if ((tmp->token == IN_REDIR || tmp->token == OUT_REDIR) && !tmp->next)
            return (head->status->status = 255, printf("error near2 `%s'\n", tmp->str), 0);
        else if (tmp && (tmp->token == HERDOC && tmp->next->token == OUT_REDIR)
        || (tmp->token == HERDOC && tmp->next->token == IN_REDIR)
        || (tmp->token == IN_REDIR && tmp->next->token == OUT_REDIR))
        return (printf("error near2 `%s'\n", tmp->str), 0);
        else if ((tmp->token == PIPE || tmp->token == HERDOC || tmp->token == IN_REDIR
            || tmp->token == OUT_REDIR || tmp->token == APPEND) && !tmp->next)
            return (head->status->status = 255, printf("error near `%s'\n", tmp->str), 0);
        else
            tmp = tmp->next;
    }
    return (1);
}
