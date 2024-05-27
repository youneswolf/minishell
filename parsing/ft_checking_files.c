/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/27 10:11:11 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_oppen_files_utiles333(t_file *t, t_holder *tmp)
{
	if (tmp->file_out && tmp->file_out[t->b]
		&& tmp->outfile_index[t->b] == t->i)
	{
		if (!is_ambiguous(tmp->file_out[t->b]))
		{
			tmp->out[t->b] = open(tmp->file_out[t->b], O_CREAT | O_RDWR, 0644);
			if (tmp->out[t->b] == -1)
				return (0);
			t->b++;
		}
		else
		{
			ft_oppen_files_utiles1(tmp, t);
			ft_null_tmp(&tmp);
		}
	}
	return (1);
}

int	ft_oppen_files_utiles(t_file *t, t_holder *tmp)
{
	if (!ft_oppen_files_utiles333(t, tmp))
		return (ft_status(1, 1), 0);
	else if (tmp->file_in && tmp->file_in[t->z]
		&& tmp->infile_index[t->z] == t->i)
	{
		tmp->in[t->z] = open(tmp->file_in[t->z], O_RDONLY);
		printf("got here the fd is %d\n", tmp->in[t->z]);
		if (!is_ambiguous(tmp->file_in[t->i]))
		{
			if (tmp->in[t->z] == -1)
				return (ft_status(1, 1), 0);
			t->z++;
		}
		else
			ft_oppen_files_utiles1(tmp, t);
	}
	return (1);
}

void	ft_oppen_utils(t_holder *tmp, t_file *t)
{
	ft_putstr_fd("bash: : ambiguous redirect\n", 2);
	ft_null_tmp(&tmp);
	ft_status(1, 1);
}

int	ft_oppen_files_nrm(t_holder *tmp, t_file *t)
{
	if (!ft_oppen_files_utiles(t, tmp))
		return (0);
	else if (tmp->append_index && tmp->append_index[t->q] == t->i)
	{
		if (tmp->append && !is_ambiguous(tmp->append[t->q]))
		{
			tmp->ap[t->q] = open(tmp->append[t->q], O_CREAT
					| O_RDWR | O_APPEND, 0644);
			if (tmp->ap[t->q] == -1)
				return (0);
			t->q++;
		}
		else
			ft_oppen_utils(tmp, t);
	}
	return (1);
}

int	ft_oppen_files(t_holder *node, t_last *status)
{
	t_holder	*tmp;
	t_file		t;
	int			e;

	tmp = node;
	(1) && (t.i = 0, t.z = 0, t.q = 0, t.b = 0, e = 0);
	while (tmp)
	{
		t.i = 0;
		while (t.i <= tmp->nbr_file)
		{
			if (!ft_oppen_files_nrm(tmp, &t))
				return (write(2, "no such file or directory\n", 26),
					ft_status(1, 1), 0);
			else if (ft_oppen_files_nrm(tmp, &t))
				;
			t.i++;
		}
		tmp = tmp->next;
	}
	return (1);
}
