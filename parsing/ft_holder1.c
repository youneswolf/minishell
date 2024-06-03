/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:37:18 by ybellakr          #+#    #+#             */
/*   Updated: 2024/06/03 13:21:44 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstnew_holder_utils(t_holder *new_)
{
	int	i;

	i = 0;
	while (new_ && i < 1000)
	{
		new_->args_built_in[i] = NULL;
		new_->args[i] = NULL;
		new_->append_index[i] = -42;
		new_->file_in[i] = NULL;
		new_->file_out[i] = NULL;
		new_->infile_index[i] = -42;
		new_->append[i] = NULL;
		new_->ap[i] = -42;
		new_->outfile_index[i] = -42;
		new_->in[i] = -42;
		new_->out[i] = -42;
		new_->her_doc[i] = NULL;
		i++;
	}
}

int	ft_lstnew_holder_uuu(t_holder *new)
{
	new->ap = malloc(sizeof(int ) * 1000);
	if (!new->ap)
		return (ft_free_if_need(new, 6), 0);
	new->out = malloc(sizeof(int ) * 1000);
	if (!new->out)
		return (ft_free_if_need(new, 7), 0);
	new->outfile_index = malloc(sizeof(int ) * 1000);
	if (!new->outfile_index)
		return (ft_free_if_need(new, 8), 0);
	new->infile_index = malloc(sizeof(int ) * 1000);
	if (!new->infile_index)
		return (ft_free_if_need(new, 9), 0);
	new->append_index = malloc(sizeof(int ) * 1000);
	if (!new->append_index)
		return (ft_free_if_need(new, 10), 0);
	new->in = malloc(sizeof(int ) * 1000);
	if (!new->in)
		return (ft_free_if_need(new, 11), 0);
	new->her_doc = malloc(sizeof(char *) * 1000);
	if (!new->her_doc)
		return (ft_free_if_need(new, 12), 0);
	(1) && (new->here = -42, new->nbr_file = 0);
	(1) && (new->cmd = NULL, new->cmd_built_in = NULL);
	ft_lstnew_holder_utils(new);
	return (new->next = NULL, 1);
}

t_holder	*ft_lstnew_holder(char *line)
{
	t_holder	*new;

	(void)line;
	new = (t_holder *)malloc(sizeof(t_holder));
	if (!new)
		return (ft_free_if_need(new, 0), NULL);
	new->args = malloc(sizeof(char *) * 1000);
	if (!new->args)
		return (ft_free_if_need(new, 1), NULL);
	new->args_built_in = malloc(sizeof(char *) * 1000);
	if (!new->args_built_in)
		return (ft_free_if_need(new, 2), NULL);
	new->file_in = malloc(sizeof(char *) * 1000);
	if (!new->file_in)
		return (ft_free_if_need(new, 3), NULL);
	new->file_out = malloc(sizeof(char *) * 1000);
	if (!new->file_out)
		return (ft_free_if_need(new, 4), NULL);
	new->append = malloc(sizeof(char *) * 1000);
	if (!new->append)
		return (ft_free_if_need(new, 5), NULL);
	if (!ft_lstnew_holder_uuu(new))
		return (NULL);
	return (new);
}

t_holder	*last_node(t_holder *head)
{
	while (head && head->next)
	{
		head = head->next;
	}
	return (head);
}

t_holder	*add_list_holder(t_holder **lst, char *line)
{
	t_holder	*new;
	t_holder	*temp;

	new = ft_lstnew_holder(line);
	temp = NULL;
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
