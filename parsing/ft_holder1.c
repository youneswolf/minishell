/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:37:18 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 10:02:07 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstnew_holder_utils(t_holder *new_)
{
	int	i;

	i = 0;
	while (i < 1000)
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

int	ft_lstnew_holder_check(t_holder *new_)
{
	if (!new_ || !new_->args || !new_->args_built_in || !new_->file_in
		|| !new_->file_out || !new_->append || !new_->ap || !new_->out
		|| !new_->outfile_index || !new_->infile_index || !new_->append_index
		|| !new_->in || !new_->her_doc)
		return (1);
	return (0);
}

t_holder	*ft_lstnew_holder(char *line)
{
	t_holder	*new;

	(void)line;
	new = (t_holder *)malloc(sizeof(t_holder));
	new->cmd = NULL;
	new->here = -42;
	new->cmd_built_in = NULL;
	new->nbr_file = 0;
	new->args = malloc(sizeof(char *) * 1000);
	new->args_built_in = malloc(sizeof(char *) * 1000);
	new->file_in = malloc(sizeof(char *) * 1000);
	new->file_out = malloc(sizeof(char *) * 1000);
	new->append = malloc(sizeof(char *) * 1000);
	new->ap = malloc(sizeof(int ) * 1000);
	new->out = malloc(sizeof(int ) * 1000);
	new->outfile_index = malloc(sizeof(int ) * 1000);
	new->infile_index = malloc(sizeof(int ) * 1000);
	new->append_index = malloc(sizeof(int ) * 1000);
	new->in = malloc(sizeof(int ) * 1000);
	new->her_doc = malloc(sizeof(char *) * 1000);
	if (ft_lstnew_holder_check(new))
		return (NULL);
	ft_lstnew_holder_utils(new);
	new->next = NULL;
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
