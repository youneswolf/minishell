void exec_export(t_line **line, t_env **env)
{
	int i;
	char *sub;
	char *value;
	t_env *tmp;
	t_line *line_tmp;
	char *join;
	int j;

	line_tmp = *line;
	tmp = *env;
	i = 0;
	j = 7;
	while (line_tmp->str[i] != '=')
		i++;
	sub = ft_substr(line_tmp->str, 0, i);
	while (tmp)
	{
		if (!ft_strncmp(sub, tmp->env, ft_strlen(sub)))
		{
			value = ft_substr(line_tmp->str, i, ft_strlen(line_tmp->str) - i);
			join = ft_strjoin(sub, value);
			tmp->env = join;
		}
		tmp = tmp->next;
	}
}