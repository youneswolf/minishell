/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_holder3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:44:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 18:04:31 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_create_hoder_utils2(t_holder *new_, t_line *tmp, int *flag, int *z)
{
	int		zz;
	int		mm;
	char	**array;

	zz = 0;
	if (new_ && tmp->flag == 1 && tmp->is_between_quote != 1)
	{
		zz = ft_count_word(tmp->str);
		if (zz >= 1)
		{
			array = ft_split1(tmp->str, ' ');
			mm = 0;
			if (array)
				new_->cmd_built_in = ft_strdup(array[0]);
			while (array && array[mm])
			{
				new_->args_built_in[(*z)++] = ft_strdup(array[mm]);
				mm++;
			}
			ft_free_2d(array);
		}
		*flag = 1;
		return (1);
	}
	return (0);
}

void	ft_create_holder_utils3(t_line *tmp, t_holder *new_, int *z)
{
	int		qq;
	int		ee;
	char	**a;

	if (new_ && ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			if (a)
				new_->cmd = ft_strdup(a[0]);
			while (a && a[ee])
				(1) && (new_->args[(*z)++] = ft_strdup(a[ee]), ee++);
			ft_free_2d(a);
		}
	}
	else if (new_)
	{
		new_->args_built_in[(*z)++] = ft_strdup(tmp->str);
		new_->cmd_built_in = ft_strdup(tmp->str);
	}
}

void	ft_create_holder_args(t_line *tmp, t_holder *new_, int *j)
{
	char	**a;
	int		qq;
	int		ee;

	a = NULL;
	if (new_ && ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			while (a && a[ee] != NULL)
			{
				new_->args[(*j)++] = ft_strdup(a[ee]);
				ee++;
			}
			ft_free_2d(a);
		}
	}
	else if (new_)
		new_->args[(*j)++] = ft_strdup(tmp->str);
}

void	ft_create_holder_args1(t_line *tmp, t_holder *new_, int *z)
{
	char	**a;
	int		qq;
	int		ee;

	if (new_ && ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			while (a && a[ee])
			{
				new_->args_built_in[(*z)++] = ft_strdup(a[ee]);
				ee++;
			}
			ft_free_2d(a);
		}
	}
	else if (new_)
		new_->args_built_in[(*z)++] = ft_strdup(tmp->str);
}

int	ft_create_holder_outfile(t_line *tmp, t_holder *n_, t_long *t)
{
	t_outfile	q;

	q.ee = 0;
	if (n_ && ft_is_there(tmp->str))
	{
		(1) && (q.a = ft_does_it_matche(tmp->str), q.qq = ft_count_2d(q.a));
		if (q.qq >= 1)
		{
			while (q.a && q.a[q.ee])
			{
				n_->file_out[(t->k)++] = ft_strdup(q.a[q.ee]);
				n_->outfile_index[(t->zzz)++] = t->index;
				(1) && ((t->index)++, q.ee++, n_->nbr_file++);
			}
			if (q.ee >= 1)
				return (ft_free_2d(q.a), ft_free_2d(n_->file_out),
					ft_putstr_fd("ambiguous redirect\n", 2), 1);
		}
	}
	else if (n_)
	{
		(1) && (n_->file_out[(t->k)++] = ft_strdup(tmp->str), n_->nbr_file++);
		(1) && (n_->outfile_index[(t->zzz)++] = t->index, (t->index)++);
	}
	return (1);
}
