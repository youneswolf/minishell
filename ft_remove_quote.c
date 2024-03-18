/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:17 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/17 22:03:20 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_remove(t_line *tmp)
{
    int     i, j;
    int     count;
    char    *str = NULL;
    int     flag;

    i = 0;
    j = 0;
    count = ft_strlen(tmp->str);
    while (tmp && tmp->str[i])
    {
        if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
        {
            flag = tmp->str[i];
            i++;
            while (tmp->str[i])
            {
                if (tmp->str[i] == flag)
                {
                    count -= 2;
                    flag = 0;
                    break;
                }
                if (tmp->str[i])
                    i++;
            }
        }
        if(tmp->str[i])
            i++;
    }
    if (count > 0)
        str = malloc(count + 1 * sizeof(char));
    if (!str)
        return ("");
    i = 0;
    while (tmp && tmp->str[i] && tmp->str)
    {
        if (tmp->str[i] != '\'' && tmp->str[i] != '\"')
        {
            str[j] = tmp->str[i];
            j++;
        }
        else if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
        {
            flag = tmp->str[i];
            i++;
            while (tmp->str[i])
            {
                if (tmp->str[i] == flag)
                {
                    flag = 0;
                    break;
                }
                else if (tmp->str[i] != flag && tmp->str[i])
                {
                    str[j] = tmp->str[i];
                    j++;
                }
                if (tmp->str[i])
                    i++;
            }
        }
        if (tmp->str[i])
            i++;
    }
    str[j] = '\0';
    free(tmp->str);
    return (str);
}

void    ft_remove_quote(t_line **str)
{
    t_line  *tmp;
    int     i;

    tmp = *str;
    i = 0;
    while (tmp)
    {
        if (tmp && (tmp->token == CMD || tmp->token == ARGS))
            tmp->str = ft_remove(tmp);
        tmp = tmp->next;
    }
    // printf("test1\n");
}