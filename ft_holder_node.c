#include "minishell.h"

void	ft_lstnew_holder_utils(t_holder *new)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
        new->args_built_in[i] = NULL;
		new->args[i] = NULL;
		new->append_index[i] = -42;
		new->file_in[i] = NULL;
		new->file_out[i] = NULL;
		new->infile_index[i] = -42;
		new->append[i] = NULL;
		new->ap[i] = -42;
		new->outfile_index[i] = -42; 
		new->in[i] = -42;
		new->out[i] = -42;
		new->her_doc[i] = NULL;
		i++;
	}
}

int		ft_lstnew_holder_check(t_holder *new)
{
	if (!new || !new->args || !new->args_built_in || !new->file_in
		|| !new->file_out || !new->append || !new->ap || !new->out
		|| !new->outfile_index || !new->infile_index || !new->append_index
		|| !new->in || new->her_doc)
			return (0);
	return(1);
}

t_holder	*ft_lstnew_holder(char *line)
{
	t_holder	*new;

	new = (t_holder *)malloc(sizeof(t_holder));
	new->cmd = NULL;
	new->here = -42;
    new->cmd_built_in = NULL;
	new->nbr_file = 0;
	new->args = malloc(sizeof(char *) * 1000);
    new->args_built_in = malloc(sizeof(char *)* 1000);
	new->file_in = malloc(sizeof(char *)* 1000);
	new->file_out = malloc(sizeof(char *)* 1000);
	new->append = malloc(sizeof(char *)* 1000);
	new->ap = malloc(sizeof(int )* 1000);
	new->out = malloc(sizeof(int )* 1000);
	new->outfile_index = malloc(sizeof(int )* 1000);
	new->infile_index = malloc(sizeof(int )* 1000);
	new->append_index = malloc(sizeof(int )* 1000);
	new->in = malloc(sizeof(int )* 1000);
	new->her_doc = malloc(sizeof(char *)* 1000);
	if (ft_lstnew_holder_check(new))
		return (NULL);
	ft_lstnew_holder_utils(new);
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

int     ft_count_pipe(t_line *head)
{
	int 	i;
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
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	ft_count_2d(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

int		ft_create_holder_utils(t_holder *new, t_line *tmp, int *flag, int *j)
{
	int		zz;
	int		mm;
	char	**array;

	zz = 0;
	mm = 0;
	if (tmp->flag == 1 && tmp->is_between_quote != 1) //&& tmp->quote == 0
	{
		zz = ft_count_word(tmp->str);
		if (zz >= 1)
		{
			array = ft_split1(tmp->str, ' ');
			new->cmd = ft_strdup(array[0]);
			while (array[mm])
			{
				new->args[*j] = ft_strdup(array[mm]);
				mm++;
				*j = *j + 1;
			}
			ft_free_2d(array);
		}
		*flag = 0;
		return (1);
	}
	return (0);
}

void	ft_create_holder_utils1(t_holder *new, t_line *tmp, int *j, int *flag)
{
	int		qq;
	char	**a;
	int		ee;

	if (ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			new->cmd = ft_strdup(a[0]);
			while (a[ee])
				(1) && (new->args[(*j)++] = ft_strdup(a[ee]), ee++);
			ft_free_2d(a);
		}
	}
	else
	{
		new->cmd = ft_strdup(tmp->str);
		new->args[(*j)++] = ft_strdup(tmp->str);
	}
	*flag = 0;
}

int	ft_create_hoder_utils2(t_holder *new, t_line *tmp, int *flag, int *z)
{
	int		zz;
	int		mm;
	char	**array;

	zz = 0;
	if (tmp->flag == 1 && tmp->is_between_quote != 1) //&& tmp->quote == 0
	{
		zz = ft_count_word(tmp->str);
		if (zz >= 1)
		{
			array = ft_split1(tmp->str, ' ');
			mm = 0;
			new->cmd_built_in = ft_strdup(array[0]);
			while (array[mm])
			{
				new->args_built_in[(*z)++] = ft_strdup(array[mm]);
				mm++;
			}
			ft_free_2d(array);
		}
		*flag = 1;
		return (1);
	}
	return (0);
}

void	ft_create_holder_utils3(t_line *tmp, t_holder *new, int *z)
{
	int		qq;
	int		ee;
	char	**a;

	if (ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			new->cmd = ft_strdup(a[0]);
			while (a[ee])
			{
				new->args[(*z)++] = ft_strdup(a[ee]);
				ee++;
			}
			ft_free_2d(a);
		}
	}
	else
	{
		new->args_built_in[(*z)++] = ft_strdup(tmp->str);
		new->cmd_built_in = ft_strdup(tmp->str);
	}
}

void	ft_create_holder_args(t_line *tmp, t_holder *new, int *j)
{
	char	**a;
	int		qq;
	int		ee;

	if (ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			while (a[ee] != NULL)
			{
				new->args[(*j)++] = ft_strdup(a[ee]);
				ee++;
			}
			ft_free_2d(a);
		}
	}
	else
		new->args[(*j)++] = ft_strdup(tmp->str);
}

void	ft_create_holder_args1(t_line *tmp, t_holder *new, int *z)
{
	char	**a;
	int		qq;
	int		ee;

	if (ft_is_there(tmp->str))
	{
		a = ft_does_it_matche(tmp->str);
		qq = ft_count_2d(a);
		ee = 0;
		if (qq >= 1)
		{
			while (a[ee])
			{
				new->args_built_in[(*z)++] = ft_strdup(a[ee]);
				ee++;
			}
			ft_free_2d(a);
		}
	}
	else
		new->args_built_in[(*z)++] = ft_strdup(tmp->str);
}

int	ft_create_holder_outfile(t_line *tmp, t_holder *new, t_long *t)
{
	char		**a;
	t_outfile	q;

	if (ft_is_there(tmp->str))
	{
		(1) && (q.ee = 0, a = ft_does_it_matche(tmp->str), q.qq = ft_count_2d(a));
		if (q.qq >= 1)
		{
			while (a && a[q.ee])
			{
				new->file_out[(t->k)++] = ft_strdup(a[q.ee]);
				new->outfile_index[(t->zzz)++] = t->index;
				(1) && ((t->index)++, q.ee++, new->nbr_file++);
			}
			if (q.ee >= 1)
				return (ft_free_2d(a), printf("bash: ambiguous redirect\n"), 0);
		}
	}
	else
	{
		new->file_out[(t->k)++] = ft_strdup(tmp->str);
		new->outfile_index[(t->zzz)++] = t->index;
		(1) && ((t->index)++, new->nbr_file++);
	}
	return (1);
}

int	ft_create_holder_infile(t_line *tmp, t_holder *new, int *n, int *sss, int *index)
{
	t_outfile	q;
	char		**a;

	if (ft_is_there(tmp->str))
	{
		(1) && (a = ft_does_it_matche(tmp->str), q.qq = ft_count_2d(a), q.ee = 0);
		if (q.qq >= 1)
		{
			while (a[q.ee])
			{
				new->file_in[(*n)++] = ft_strdup(a[q.ee]);
				(1) && (q.ee++, new->nbr_file++, (*index)++);
				new->infile_index[(*sss)++] = *index;
			}
			if (q.ee >= 1)
				return (ft_free_2d(a), printf("bash: ambiguous redirect\n"), 0);
		}
	}
	else
	{
		new->file_in[(*n)++] = ft_strdup(tmp->str);
		new->infile_index[(*sss)++] = *index;
		(1) && ((*index)++, new->nbr_file++);
	}
	return (1);
}


int	ft_create_holder_append(t_line *tmp, t_holder *new, t_long *t)
{
	char		**aa;
	t_outfile	q;

	if (tmp && tmp->next && ft_is_there(tmp->next->str))
	{
		(1) && (aa = ft_does_it_matche(tmp->next->str), q.qq = ft_count_2d(aa), q.ee = 0);
		if (q.qq >= 1)
		{
			while (aa[q.ee])
			{
				new->append[(t->a)++] = ft_strdup(aa[q.ee]);
				(1) && (q.ee++, (t->index)++, new->nbr_file++);
				new->append_index[(t->www)++] = t->index;
			}
			if (q.ee >= 1)
				return (ft_free_2d(aa), printf("bash: ambiguous redirect\n"), 0);
		}
	}
	else
	{
		new->append[(t->a)++] = ft_strdup(tmp->next->str);
		new->append_index[(t->www)++] = t->index;
		(1) && ((t->index)++, new->nbr_file++);
	}
	return (1);
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

int	ft_utils_norm_utils(t_line *tmp, t_holder *new, t_long *t)
{
	if (tmp->token == OUT_FILE)
	{
		if (!ft_create_holder_outfile(tmp, new, t))
			return (0);
	}
	else if (tmp->token == IN_FILE)
	{
		if (!ft_create_holder_infile(tmp, new, &t->n, &t->sss, &t->index))
			return (0);
	}
	else if (tmp->token == APPEND)
	{
		ft_create_holder_append(tmp, new, t);
		t->does = 1;
	}
	else if (tmp->token == HERDOC && t->a < 1024)
		if (tmp->next)
		{
			if (t->does == 0)
				new->here = 1;
			else
				new->here = 0;
			new->her_doc[t->l++] = ft_strdup(tmp->next->str);
		}
	return (1);
}

int	ft_utils_norm(t_line *tmp, t_holder *new, t_long *t)
{
	if (tmp->token == CMD && tmp->is_it_built_in == 1)
	{
		if (ft_create_hoder_utils2(new, tmp, &t->flag, &t->z))
			;
		else
			ft_create_holder_utils3(tmp, new, &t->z);
		t->flag = 1;
	}
	else if (tmp->token == ARGS && t->flag == 0)
	{
		ft_create_holder_args(tmp, new, &t->j);
		t->does = 1;
	}
	else if(tmp->token == ARGS && t->flag == 1)
	{
		ft_create_holder_args1(tmp, new, &t->z);
		t->does = 1;
	}
	else if (!ft_utils_norm_utils(tmp, new, t))
		return (0);
	return (1);
}

int	ft_create_holder_node_utils(t_line *tmp, t_holder *new, t_long *t, t_holder *holder)
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

t_holder    *ft_create_holder_node(t_line *node, char *line)
{
	t_holder    *holder;
	t_holder    *new;
	t_long		t;
	t_line      *tmp;

	(1) && (t.i = 0, ft_ini(&t), tmp = node,
		t.c = ft_count_pipe(node), holder = NULL);
	while (tmp && (t.i++ <= t.c))
	{
		(1) && (t.j = 0, t.flag = 0, t.index = 0);
		new = add_list_holder(&holder, line);
		while (tmp)
		{
			if (tmp->next && tmp->token == PIPE)
			{
				tmp = tmp->next;
				break;
			}
			if (!ft_create_holder_node_utils(tmp, new, &t, holder))
				return (NULL);
			tmp = tmp->next;
		}
	}
	return (holder);
}
