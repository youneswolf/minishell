/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:33:43 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 12:35:22 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_env **str)
{
	t_env	*to_be_free;
	t_env	*prev;

	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->env);
		free(prev);
	}
}

void	exec_fcts(t_env *head, t_env *node)
{
	ft_sort_list(&head);
	ft_print_export(head);
	ft_free_env(&node);
	ft_status(1, 0);
}

void	set_node_things(t_env **node, t_env *tmp)
{
	(*node) = malloc(sizeof(t_env));
	(*node)->env = ft_strdup(tmp->env);
	(*node)->deleted = tmp->deleted;
	(*node)->next = NULL;
}

void	declare_export(t_env *env)
{
	t_env	*tmp;
	t_env	*last_node;
	t_env	*node;
	t_env	*head;

	(1) && (head = NULL, tmp = env);
	while (tmp)
	{
		if (tmp->deleted == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		set_node_things(&node, tmp);
		if (!head)
			head = node;
		else
		{
			last_node = get_last(&head);
			last_node->next = node;
		}
		tmp = tmp->next;
	}
	node = head;
	exec_fcts(head, node);
}

char	*ft_add_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_value;

	if (str)
	{
		i = 1;
		j = 2;
		new_value = malloc(ft_strlen(str) + 3);
		if (!new_value)
			return (NULL);
		new_value[0] = '=';
		new_value[1] = 34;
		while (str && str[i] && str[i] != '=')
		{
			new_value[j] = str[i];
			i++;
			j++;
		}
		new_value[j++] = 34;
		new_value[j] = '\0';
		free(str);
		return (new_value);
	}
	return (str);
}
