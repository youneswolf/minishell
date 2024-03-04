void remove_node(t_env **mini_env, int i)
{
	t_env *tmp;
	t_env *join;
	t_env *head;
	int j;

	head = *mini_env;
	j = 0;
	while (*mini_env)
	{
		if (j == i - 1)
		{
			join = (*mini_env)->next;
			(*mini_env)->next = (*mini_env)->next->next;

		}
		*mini_env = (*mini_env)->next;
		j++;
	}
	*mini_env = head;
}

void exec_unset(t_env **mini_env, t_line **line)
{
	t_env *tmp;
	char *sub;
	char *value;
	t_line *tmp1;
	int i;
	int j;

	tmp1 = *line;
	tmp = *mini_env;
	while (tmp1)
	{
		value = ft_strjoin(tmp1->str, "=");
		i = 0;
		while (tmp)
		{
			if (!ft_strncmp(value, tmp->env, ft_strlen(value)))
			{
				remove_node(mini_env, i);
			}
			tmp = tmp->next;
			i++;
		}
	tmp1 = tmp1->next;
	}
}