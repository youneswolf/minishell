/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checking_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/11 17:06:58 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int is_ambiguous(char *str)
{
    int i = 0;
    int j = 0;
    if (str && !str[0])
        return (1);
    if (str && str[0] == 32)
    {
        while(str[i] && str[i] == 32)
            i++;
        if (!str[i])
            return (1);
    }
    i = 0;
    while (str && str[i])
    {
        if (str[i] == ' ')
            j = 1;
        if (j == 1 && ft_isalnum(str[i]))
            return (1);
        i++;
    }  
    return (0);
}

void	ft_free_2d_am(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

void ft_null_tmp(t_holder **tmp)
{
    if ((*tmp)->cmd)
    {
        free((*tmp)->cmd);
        (*tmp)->cmd = NULL;
    }
    if ((*tmp)->args[0])
    {
    ft_free_2d_am((*tmp)->args);
    (*tmp)->args[0] = NULL;
    }
    if ((*tmp)->cmd_built_in)
    {
        free((*tmp)->cmd_built_in);
        (*tmp)->cmd_built_in = NULL;
    }
    if ((*tmp)->args_built_in[0])
    {
        ft_free_2d_am((*tmp)->args_built_in);
        (*tmp)->args_built_in[0] = NULL;
    }
}

void    ft_oppen_files_utiles1(t_holder *tmp, t_file *t)
{
    printf("bash: %s: ambiguous redirect\n", tmp->file_in[t->z]);
    ft_null_tmp(&tmp);
    ft_status(1, 1);
}

int ft_oppen_files_utiles(t_file *t, t_holder *tmp)
{
    if (tmp->outfile_index[t->b] == t->i)
    {
        if(!is_ambiguous(tmp->file_out[t->b]))
        {
            tmp->out[t->b] = open(tmp->file_out[t->b], O_CREAT| O_RDWR, 0644);
            if (tmp->out[t->b] == -1)
                return (write(2, "no such file or directory\n", 26), ft_status(1, 1), 0);
            t->b++;
        }
        else
            ft_null_tmp(&tmp);
    }
    else if (tmp->infile_index[t->z] == t->i)
    {
        tmp->in[t->z] = open(tmp->file_in[t->z], O_RDONLY);
        if(!is_ambiguous(tmp->file_in[t->i]))
        {
            if (tmp->in[t->z] == -1)
                return (write(2, "no such file or directory\n", 24), ft_status(1, 1), 0);
            t->z++;
        }
        else
            ft_oppen_files_utiles1(tmp, t);
    }
    return (1);
}

void    ft_oppen_utils(t_holder *tmp, t_file *t)
{
    printf("bash: %s: ambiguous redirect\n", tmp->append[t->q]);
    ft_null_tmp(&tmp);
    ft_status(1, 1);
}

int    ft_oppen_files(t_holder *node, t_last *status)
{
    t_holder    *tmp;
    t_file      t;

    tmp = node;
    (1) && (t.i = 0, t.z = 0, t.q = 0, t.b = 0);
    while (tmp && (t.i < tmp->nbr_file))
    {
        if (!ft_oppen_files_utiles(&t, tmp))
            return (0);
        else if (tmp->append_index[t.q] == t.i)
        {
            if(!is_ambiguous(tmp->append[t.q]))
            {
                tmp->ap[t.q] = open(tmp->append[t.q], O_CREAT| O_RDWR | O_APPEND, 0644);
                if (tmp->ap[t.q] == -1)
                    return (write(2, "no such file or directory\n", 26), ft_status(1, 1), 0);
                t.q++;
            }
            else
                ft_oppen_utils(tmp, &t);
        }  
        t.i++;
    }
    return (ft_status(1, 0), 1);
}
