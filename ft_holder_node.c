/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:04:30 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/18 06:15:29 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_holder	*ft_lstnew_holder(void)
{
	t_holder	*new;

    int i = 0;
	new = (t_holder *)malloc(sizeof(t_holder));
    new->cmd = NULL;
    new->args = malloc(sizeof(char *) * 1024);
    new->file_in = malloc(sizeof(char *) * 1024);
    new->file_out = malloc(sizeof(char *) * 1024);
    new->append = malloc(sizeof(char *) * 1024);
    new->ap = malloc(sizeof(int ) * 1024);
    new->out = malloc(sizeof(int ) * 1024);
    new->in = malloc(sizeof(int ) * 1024);
    while (i < 1024)
    {
        new->args[i] = NULL;
        new->file_in[i] = NULL;
        new->file_out[i] = NULL;
        new->append[i] = NULL;
        new->ap[i] = -42;
        new->in[i] = -42;
        new->out[i] = -42;
        i++;
    }
	if (!new)
    {
		printf("failed\n");
        return (NULL);
    }
	new->next = NULL;
	return (new);
}

t_holder *last_node(t_holder *head)
{
    while (head && head->next)
    {
        head = head->next;
    }
    return (head);
}

t_holder	*add_list_holder(t_holder **lst)
{
    t_holder *new = ft_lstnew_holder();
	t_holder	*temp = NULL;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp && temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
    return (last_node(*lst));
}

int     ft_count_pipe(t_line *head)
{
    int i;
    t_line  *tmp;

    i = 0;
    tmp = head;
    while (tmp)
    {
        if (tmp->token == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

t_holder    *ft_create_holder_node(t_line *node)
{
    t_holder    *holder= NULL;
    t_holder    *new;
    t_line      *tmp;
    t_line      *tmp1;

    int c = ft_count_pipe(node);
    int i = 0;
    int j = 0, k = 0, w = 0, a = 0, n = 0;
    tmp = node;
    tmp1 = tmp;
    while (i <= c)
    {
        j = 0;
        new = add_list_holder(&holder);
        while (tmp)
        {
            if (tmp->next && tmp->str[0] == '|')
            {
                tmp = tmp->next;
                break;
            }
            if (tmp->token == CMD)
            {
                new->cmd = tmp->str;
                new->args[j++] = tmp->str;
            }
            else if (tmp->token == ARGS)
                new->args[j++] = tmp->str;
            else if (tmp->token == OUT_FILE)
                new->file_out[k++] = tmp->str;
            else if (tmp->token == OUT_FILE)
                 new->file_out[w++] = tmp->str;
            else if (tmp->token == IN_FILE)
                 new->file_in[n++] = tmp->str;
            else if (tmp->token == APPEND)
            {
                if (tmp->next)
                    new->append[a++] = tmp->next->str;
            }
            tmp = tmp->next;
        }
        i++;
    }
    return (holder);
}