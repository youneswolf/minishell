/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:54:50 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 15:00:03 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_holder_infile(t_line *tmp, t_holder *new_, t_long *t)
{
	t_outfile	q;

	q.ee = 0;
	if (ft_is_there(tmp->str))
	{
		(1) && (q.a = ft_does_it_matche(tmp->str), q.qq = ft_count_2d(q.a));
		if (q.qq >= 1)
		{
			while (q.a[q.ee])
			{
				new_->file_in[(t->n)++] = ft_strdup(q.a[q.ee]);
				(1) && (q.ee++, new_->nbr_file++, (t->index)++);
				new_->infile_index[(t->sss)++] = t->index;
			}
			if (q.ee >= 1)
				return (ft_free_2d(q.a), ft_free_2d(new_->file_in),
					ft_putstr_fd("ambiguous redirect\n", 2), 1);
		}
	}
	else
	{
		new_->file_in[(t->n)++] = ft_strdup(tmp->str);
		(1) && ((t->index)++, new_->infile_index[(t->sss)++] = t->index);
	}
	return (new_->nbr_file++, 1);
}

int	ft_create_holder_append(t_line *tmp, t_holder *new_, t_long *t)
{
	t_outfile	q;

	if (tmp && tmp->next && ft_is_there(tmp->next->str))
	{
		(1) && (q.ee = 0, tmp = tmp->next);
		(1) && (q.a = ft_does_it_matche(tmp->str), q.qq = ft_count_2d(q.a));
		if (q.qq >= 1)
		{
			while (q.a[q.ee])
			{
				new_->append[(t->a)++] = ft_strdup(q.a[q.ee]);
				(1) && (q.ee++, (t->index)++, new_->nbr_file++);
				new_->append_index[(t->www)++] = t->index;
			}
			if (q.ee >= 1)
				return (ft_free_2d(q.a), ft_free_2d(new_->append),
					ft_putstr_fd("ambiguous redirect\n", 2), 0);
		}
	}
	else
	{
		new_->append[(t->a)++] = ft_strdup(tmp->next->str);
		(1) && ((t->index)++, new_->append_index[(t->www)++] = t->index);
	}
	return (new_->nbr_file++, 1);
}

void	ft_ini(t_long *t)
{
	t->a = 0;
	t->is_out = 0;
	t->index = 0;
	t->a = 0;
	t->does = 0;
	t->flag = 1;
	t->j = 0;
	t->k = 0;
	t->l = 0;
	t->mm = 0;
	t->n = 0;
	t->sss = 0;
	t->w = 0;
	t->www = 0;
	t->z = 0;
	t->zz = 0;
	t->zzz = 0;
	t->c = 0;
	t->i = 0;
}

int	ft_utils_norm_utils(t_line *tmp, t_holder *new_, t_long *t)
{
	if (tmp->token == OUT_FILE)
	{
		if (!ft_create_holder_outfile(tmp, new_, t))
			return (0);
	}
	else if (tmp->token == IN_FILE)
	{
		if (!ft_create_holder_infile(tmp, new_, t))
			return (0);
	}
	else if (tmp->token == APPEND)
		(1) && (ft_create_holder_append(tmp, new_, t), t->does = 1);
	else if (tmp->token == HERDOC && t->a < 1024)
	{
		if (tmp->next)
		{
			if (t->does == 0)
				new_->here = 1;
			else
				new_->here = 0;
			new_->her_doc[t->l++] = ft_strdup(tmp->next->str);
		}
	}
	return (1);
}

int	ft_utils_norm(t_line *tmp, t_holder *new_, t_long *t)
{
	if (tmp->token == CMD && tmp->is_it_built_in == 1)
	{
		if (ft_create_hoder_utils2(new_, tmp, &t->flag, &t->z))
			;
		else
			ft_create_holder_utils3(tmp, new_, &t->z);
		t->flag = 1;
	}
	else if (tmp->token == ARGS && t->flag == 0)
	{
		ft_create_holder_args(tmp, new_, &t->j);
		t->does = 1;
	}
	else if (tmp->token == ARGS && t->flag == 1)
	{
		ft_create_holder_args1(tmp, new_, &t->z);
		t->does = 1;
	}
	else if (!ft_utils_norm_utils(tmp, new_, t))
		return (0);
	return (1);
}
