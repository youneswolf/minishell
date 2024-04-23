#include "minishell.h"

t_holder	*ft_lstnew_holder(char *line)
{
	t_holder	*new;

	int i = 0;
	new = (t_holder *)malloc(sizeof(t_holder));
	new->cmd = NULL;
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
	new->in = malloc(sizeof(int )* 1000);
	new->her_doc = malloc(sizeof(char *)* 1000);
	while (i < 1000)
	{
        new->args_built_in[i] = NULL;
		new->args[i] = NULL;
		new->file_in[i] = NULL;
		new->file_out[i] = NULL;
		new->infile_index[i] = -1337;
		new->append[i] = NULL;
		new->ap[i] = -42;
		new->outfile_index[i] = -1337; 
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

int	ft_count_2d(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

t_holder    *ft_create_holder_node(t_line *node, char *line)
{
	t_holder    *holder= NULL;
	t_holder    *new;
	t_line      *tmp;
	int			zzz, www;
	int			sss;
	t_line      *tmp1;

	int c = ft_count_pipe(node);
	int i = 0;
	www = 0;
	int j = 0, k = 0, w = 0, a = 0, n = 0, l = 0, z = 0, zz = 0, flag = 1;
	int	mm = 0;
	sss = 0;
	zzz = 0;
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
				if (tmp->flag == 1) //&& tmp->quote == 0
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
					if (ft_is_there(tmp->str))
					{
						char **a = ft_does_it_matche(tmp->str);
						int qq = ft_count_2d(a);
						int	ee = 0;
						if (qq >= 1)
						{
							new->cmd = ft_strdup(a[0]);
							while (a[ee])
							{
								new->args[j++] = ft_strdup(a[ee]);
								ee++;
							}
							// ft_free_2d(a);
						}
					}
					else
					{
						new->cmd = tmp->str;
						new->args[j++] = tmp->str;
					}
					new->args[j] = NULL;
					flag = 0;
				}
				flag = 0;
			}
            if (tmp->token == CMD && tmp->is_it_built_in == 1)
            {
				if (tmp->flag == 1) //&& tmp->quote == 0
				{
					zz = ft_count_word(tmp->str);
					if (zz > 1)
					{
						char **array = ft_split1(tmp->str, ' ');
						mm = 0;
						new->cmd_built_in = ft_strdup(array[0]);
						while (array[mm])
						{
							new->args_built_in[z++] = ft_strdup(array[mm]);
							mm++;
						}
						ft_free_2d(array);
					}
					flag = 1;
				}
				else
				{	
					if (ft_is_there(tmp->str))
					{
						char **a = ft_does_it_matche(tmp->str);
						int qq = ft_count_2d(a);
						int	ee = 0;
						if (qq >= 1)
						{
							new->cmd = ft_strdup(a[0]);
							while (a[ee])
							{
								new->args[z++] = ft_strdup(a[ee]);
								ee++;
							}
							// ft_free_2d(a);
						}
					}
					else
					{
						new->args_built_in[z++] = tmp->str;
						new->cmd_built_in = tmp->str;
					}
					new->args_built_in[z] = NULL;
				}
                flag = 1;
            }
			// if (tmp->token == ARGS && flag == 42)
			// {
			// 	if (ft_cmp_built_in(tmp->str) == 1)
			// 		flag = 1;
			// 	else
			// 	 	flag = 0;
			// }
			if (tmp->token == ARGS && flag == 0)
			{
				if (ft_is_there(tmp->str))
				{
					char **a = ft_does_it_matche(tmp->str);
					int qq = ft_count_2d(a);
					int	ee = 0;
					if (qq >= 1)
					{
						while (a[ee] != NULL)
						{
							new->args[j++] = ft_strdup(a[ee]);
							ee++;
						}
						// ft_free_2d(a);
					}
				}
				else
				{
					new->args[j++] = tmp->str;
				}
				new->args[j] = NULL;
			}
        	if(tmp->token == ARGS && flag == 1)
			{
				if (ft_is_there(tmp->str))
				{
					char **a = ft_does_it_matche(tmp->str);
					int qq = ft_count_2d(a);
					int	ee = 0;
					if (qq >= 1)
					{
						while (a[ee])
						{
							new->args_built_in[z++] = ft_strdup(a[ee]);
							ee++;
						}
						// ft_free_2d(a);
					}
				}
				else
				{
                	new->args_built_in[z++] = tmp->str;
					// printf("new->args %s\n", tmp->str);
				}
				new->args_built_in[z] = NULL;
			}
			if (tmp->token == OUT_FILE)
			{
				if (ft_is_there(tmp->str))
				{
					char **a = ft_does_it_matche(tmp->str);
					int qq = ft_count_2d(a);
					int	ee = 0;
					if (qq >= 1)
					{
						while (a && a[ee])
						{
							new->file_out[k++] = ft_strdup(a[ee]);
							ee++;
							new->nbr_file++;
						}
						// ft_free_2d(a);
					}
				}
				else
				{
					new->file_out[k++] = tmp->str;
					new->outfile_index[zzz++] = tmp->status->index;
					new->nbr_file++;
				}
				// new->outfile_index[zzz] = -1337;
				new->file_out[k] = NULL;
			}
			if (tmp->token == IN_FILE)
			{
				if (ft_is_there(tmp->str))
				{
					char **a = ft_does_it_matche(tmp->str);
					int qq = ft_count_2d(a);
					int	ee = 0;
					if (qq >= 1)
					{
						while (a[ee])
						{
							new->file_in[n++] = ft_strdup(a[ee]);
							ee++;
							new->nbr_file++;
						}
						// ft_free_2d(a);
					}
				}
				else
				{
					new->file_in[n++] = tmp->str;
					new->infile_index[sss++] = tmp->status->index;
					new->nbr_file++;
				}
				new->file_in[n] = NULL;
			}
			if (tmp->token == APPEND)
			{
				if (tmp->next)
				{
					if (ft_is_there(tmp->next->str))
					{
						char **aa = ft_does_it_matche(tmp->next->str);
						int qq = ft_count_2d(aa);
						int	ee = 0;
						if (qq >= 1)
						{
							while (aa[ee])
							{
								new->append[a++] = ft_strdup(aa[ee]);
								ee++;
								new->nbr_file++;
							}
						}
						// ft_free_2d(aa);
					}
					else
						{
							new->append_index[www++] = tmp->status->index;
							new->append[a++] = tmp->next->str;
							new->nbr_file++;
						}
					new->append[a] = NULL;
				}
			}
			if (tmp->token == HERDOC && a < 1024)
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