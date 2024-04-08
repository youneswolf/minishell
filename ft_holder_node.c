/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:04:30 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/08 19:57:34 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_holder	*ft_lstnew_holder(char *line)
{
	t_holder	*new;

	int i = 0;
	new = (t_holder *)malloc(sizeof(t_holder));
	new->cmd = NULL;
    new->cmd_built_in = NULL;
	new->args = malloc(sizeof(char *) * 1024);
    new->args_built_in = malloc(sizeof(char *) * 1024);
	new->file_in = malloc(sizeof(char *) * 1024);
	new->file_out = malloc(sizeof(char *) * 1024);
	new->append = malloc(sizeof(char *) * 1024);
	new->ap = malloc(sizeof(int ) * 1024);
	new->out = malloc(sizeof(int ) * 1024);
	new->in = malloc(sizeof(int ) * 1024);
	new->her_doc = malloc(sizeof(char *) * 1024);
	while (i < 1024)
	{
        new->args_built_in[i] = NULL;
		new->args[i] = NULL;
		new->file_in[i] = NULL;
		new->file_out[i] = NULL;
		new->append[i] = NULL;
		new->ap[i] = -42;
		new->in[i] = -42;
		new->out[i] = -42;
		new->her_doc[i] = NULL;
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

t_holder	*add_list_holder(t_holder **lst, char *line)
{
	t_holder *new = ft_lstnew_holder(line);
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

int		ft_count_word(char *str)
{
	int i = 0, count = 0;

	while (str && str[i])
	{
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

t_holder    *ft_create_holder_node(t_line *node, char *line)
{
	t_holder    *holder= NULL;
	t_holder    *new;
	t_line      *tmp;
	t_line      *tmp1;

	int c = ft_count_pipe(node);
	int i = 0;
	int j = 0, k = 0, w = 0, a = 0, n = 0, l = 0, z = 0, zz = 0, flag = 1;
	int	mm = 0;
	tmp = node;
	tmp1 = tmp;
	while (i <= c)
	{
		j = 0;
		// tmp->flag = 1;
		new = add_list_holder(&holder, line);
		flag = 42;
		while (tmp)
		{
			if (tmp->next && tmp->str[0] == '|')
			{
				tmp = tmp->next;
				break;
			}
			if (tmp->token == CMD && tmp->is_it_built_in == 0)
			{
				if (tmp->flag == 1 && tmp->quote == 0)
				{
					zz = ft_count_word(tmp->str);
					if (zz > 1)
					{
						char **array = ft_split1(tmp->str, ' ');
						new->cmd = ft_strdup(array[0]);
						while (array[mm])
						{
							new->args[j++] = ft_strdup(array[mm]);
							mm++;
						}
						ft_free_2d(array);
					}
					flag = 0;
				}
				else 
				{	
					new->cmd = tmp->str;
					new->args[j++] = tmp->str;
				}
				flag = 0;
			}
            else if (tmp->token == CMD && tmp->is_it_built_in == 1)
            {
				if (tmp->flag == 1 && tmp->quote == 0)
				{
					zz = ft_count_word(tmp->str);
					if (zz > 1)
					{
						char **array = ft_split1(tmp->str, ' ');
						mm = 0;
						new->cmd_built_in = ft_strdup(array[0]);
						while (array[mm])
						{
							new->args_built_in[zz++] = ft_strdup(array[mm]);
							mm++;
						}
						ft_free_2d(array);
					}
					flag = 1;
				}
				else 
				{	
                	new->args_built_in[z++] = tmp->str;
                	new->cmd_built_in = tmp->str;
				}
                flag = 1;
            }
			else if (tmp->token == ARGS && flag == 0)
				new->args[j++] = tmp->str;
            else if (tmp->token == ARGS && flag == 1)
                new->args_built_in[z++] = tmp->str;
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
			else if (tmp->token == HERDOC && a < 1024)
			{
				if (tmp->next)
					new->her_doc[l++] = tmp->next->str;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (holder);
}