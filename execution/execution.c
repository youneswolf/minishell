/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:25 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:39:45 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd    *ft_set_cmd(t_line   *head)
{
    t_line  *tmp;
    t_cmd   *cmd;
    int     i;

    tmp = head;
    while (head->token != PIPE)
    {
        if (head->token == CMD)
            cmd->cmd = head->str;
        else if (head->token == ARGS)
            cmd->arg[i] = head->str;
        else if (head->token == OUT_REDIR)
            cmd->in_or_out = 1;
        else if (head->token == OUT_REDIR)
            cmd->in_or_out = 0;
        else if (head->token == IN_FILE)
            cmd->infile = head->str;
        else if (head->token == OUT_FILE)
            cmd->outfile = head->str;
        i++;
        head = head->next;
    }
}

// void    ft_run_one_cmd(t_cmd *head)
// {

// }

// void    ft_execute_cmd(t_line *head)
// {
//     int i;
//     t_line  *tmp;
//     t_cmd   *cmd;

//     i = 0;
//     tmp = head;
//     while (head)
//     {
//         if (head->token == CMD)
//             i++;
//         head = head->next;
//     }
//     cmd = ft_set_cmd(head);
//     if (i = 1)
//         ft_run_one_cmd(cmd);
    
// }