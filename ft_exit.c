/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:20:58 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/06 17:05:05 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_cmp(char *s, char *s1)
{
    int i;

    i = 0;
    while (s && s1 && s[i] && s1[i] && s[i] == s1[i])
        i++;
    return (s[i] - s1[i]);
}

int     ft_is_numeric(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (0);
        i++;
    }
    return (1);
}

unsigned long  ft_atoi(char *str)
{
    unsigned long    j;
    int     sign, i;

    j = 0;
    sign = 0;
    i = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        if (str[0] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    {
        j = j * 10 + str[i] - 48;
        i++;
    }
    if (sign == -1)
        return (-j);
    return (j);
}

void    ft_exit(t_holder *str)
{
    t_holder *tmp, *tmp1;
    unsigned long t;
    int     i;
    char *s;

    tmp1 = str;
    i = 0;
    // while (tmp)
    // {
    //     if (tmp->token && tmp->is_it_built_in == 1 && ft_strlen(tmp->str) == 4
    //         && ft_cmp("exit", tmp->str))
    //     {
    // tmp1 = tmp->next;
    // s = tmp->next->str;
    while (tmp1 && tmp1->args_built_in[i])
        i++;
    if (i == 1)
        (printf("exit\n"), exit(0)); //, tmp->status1->status = 0
    else if (i > 2 && ft_is_numeric(tmp1->args_built_in[1]))
        (write(2, "exit\n", 4), write(2, "bash: exit: too many arguments\n", 33)); //, tmp->status1->status = 1
    else if (tmp1->args_built_in[1] && !ft_is_numeric(tmp1->args_built_in[1]))
        (printf("exit\n"), printf("exit: %s: numeric argument required", s), exit(1)); //, tmp->status1->status = 255
    else if (i == 2 && ft_is_numeric(tmp1->args_built_in[1])
        && (ft_atoi(tmp1->args_built_in[1]) <= 9223372036854775807  || ft_atoi(tmp1->args_built_in[1]) >= -922337203685477588))
        (printf("exit\n"), exit(0)); //, tmp->status1->status = ft_atoi(tmp1->str)
    else if (tmp1->args_built_in[1] && ft_is_numeric(tmp1->args_built_in[1]) &&
        (ft_atoi(tmp1->args_built_in[1]) > 9223372036854775807  || ft_atoi(tmp1->args_built_in[1]) < -922337203685477588))
        (printf("exit\n"), printf("exit: %s: numeric argument required", s), exit(1)); //tmp->status1->status = 255,
        // }
        // tmp = tmp->next;
    // }
}
