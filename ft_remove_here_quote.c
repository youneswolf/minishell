/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_here_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:17 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/18 17:17:24 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_remove_utils_here(char *str)
{
    int count;
    int flag;
    int i;

    count = ft_strlen(str);
    i = 0;
    while (str && str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            (1) && (flag = str[i], i++);
            while (str[i])
            {
                if (str[i] == flag)
                {
                    (1) && (count -= 2, flag = 0);
                    break;
                }
                i++;
            }
        }
        if(str[i])
            i++;
    }
    return (count);
}

char    *ft_remove_utils2_here(char *tmp_str, char *str, int j, int i)
{
    int flag;

    while (tmp_str && str[i] && str)
    {
        if (str[i] != '\'' && str[i] != '\"')
            (1) && (str[j] = str[i] , j++);
        else if (str[i] == '\"' || str[i] == '\'')
        {
            (1) && (flag = str[i], i++);
            while (str[i])
            {
                if (str[i] == flag)
                {
                    flag = 0;
                    break;
                }
                else if (str[i] != flag && str[i])
                    (1) && (str[j] = str[i], j++);
                i++;
            }
        }
        if (&str[i])
            i++;
    }
    return (str[j] = '\0', free(tmp_str), str);
}

char    *ft_remove_here(char *str)
{
    int     j;
    int     count;
    char    *str_ret = NULL;
    int     i;

    j = 0;
    i = 0;
    count = ft_remove_utils_here(str);
    if (count > 0)
        str_ret = malloc(count + 1 * sizeof(char));
    if (!str_ret)
        return (NULL);
        // return (free(str), ft_free_list(tmp), "");
    str_ret = ft_remove_utils2_here(str_ret, str, j, i);
    return (str_ret);
}

// void    ft_remove_quote_here(char *str, char *line)
// {
//     int     i;

//     i = 0;
//     while (tmp)
//     {
//         if (tmp && (tmp->token == CMD || tmp->token == ARGS))
//         {
//             // if (tmp->token == DELIMITER)
//             //     tmp->delimiter_quote = 1;
//             // free(tmp->str);
//             tmp->str = ft_remove(tmp, line);
//         }
//         tmp = tmp->next;
//     }
// }