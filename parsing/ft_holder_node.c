/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:46:14 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 14:57:16 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_holder_node_utils(t_line *tmp, t_holder *new,
	t_long *t, t_holder *holder)
{
	if (tmp->token == CMD && tmp->is_it_built_in == 0)
	{
		if (ft_create_holder_utils(new, tmp, &t->flag, &t->j))
			t->does = 1;
		else
			ft_create_holder_utils1(new, tmp, &t->j, &t->flag);
		t->flag = 0;
	}
	if (!ft_utils_norm(tmp, new, t))
		return (ft_free_holder(&holder), 0);
	return (1);
}

t_holder	*ft_create_holder_node(t_line *node, char *line)
{
	t_holder	*holder;
	t_holder	*new;
	t_long		t;
	t_line		*tmp;

	(1) && (t.i = 0, ft_ini(&t), tmp = node,
		t.c = ft_count_pipe(node), holder = NULL);
	while (tmp && (t.i++ <= t.c))
	{
		(1) && (t.j = 0, t.flag = 0, t.index = 0);
		ft_ini(&t);
		new = add_list_holder(&holder, line);
		while (tmp)
		{
			if (tmp->next && tmp->token == PIPE)
			{
				tmp = tmp->next;
				break ;
			}
			if (!ft_create_holder_node_utils(tmp, new, &t, holder))
				return (NULL);
			tmp = tmp->next;
		}
	}
	return (holder);
}
