/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:04:30 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/13 17:05:07 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_holder	*ft_lstnew_holder(void)
{
	t_holder	*new;

    int i = 0;
	new = (t_holder *)malloc(sizeof(t_holder));
    new->args = malloc(sizeof(char *) * 1024);
    new->file_in = malloc(sizeof(char *) * 1024);
    new->file_out = malloc(sizeof(char *) * 1024);
    new->append = malloc(sizeof(char *) * 1024);
    while (i < 1024)
    {
        new->args[i] = NULL;
        new->file_in[i] = NULL;
        new->file_out[i] = NULL;
        new->append[i] = NULL;
        i++;
    }
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	add_list_holder(t_holder **lst, t_holder *new)
{
	t_holder	*temp;

	// new = ft_lstnew_holder();
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
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

    int c = ft_count_pipe(node);
    int i = 0;
    int j = 0, k = 0, w = 0, a = 0;
    tmp = node;
    while (i <= c)
    {
        new = ft_lstnew_holder();
        while (tmp)
        {
            if (tmp->str[0] == '|')
                tmp = tmp->next;
            else if (tmp->token == CMD)
            {
                new->cmd = tmp->str;
                new->args[j++] = tmp->str;
            }
            else if (tmp->token == ARGS)
                new->args[j++] = tmp->str;
            else if (tmp->token == OUT_FILE)
                new->file_out[k++] = tmp->str;
            else if (tmp->token == IN_FILE)
                 new->file_out[w++] = tmp->str;
            else if (tmp->token == IN_FILE)
                 new->file_out[w++] = tmp->str;
            else if (tmp->token == APPEND)
                 new->append[a++] = tmp->str;
            tmp = tmp->next;
        }
        add_list_holder(&holder, new);
        holder = holder->next;
        i++;
    }
    return (holder);
}