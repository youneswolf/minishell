#include "minishell.h"
int check_is_all_printed(t_env **env)
{
	t_env *tmp = *env;
	while (tmp)
	{
		if (tmp->printed == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
void exec_export(t_holder **holder, t_env **env)
{
	int i;
	char *node_env;
	char *var_name;
	char *value;
	t_env *tmp;
	t_holder *line_tmp;
	char *join;
	int j;
	line_tmp = *holder;
	tmp = *env;
	if (!line_tmp->args_built_in[1])
	{
	while (check_is_all_printed(env))
	{
		*env = tmp;
		while((*env)->next)
		{
			node_env = (*env)->env;
			if (ft_strcmp(node_env ,(*env)->next->env) < 0)
				node_env = (*env)->next->env;
			(*env) = (*env)->next;
		}
		printf("declare -x %s\n", node_env);
	}
	}
	else
	{
	i = 0;
	j = 7;
	while (line_tmp->args_built_in[1][i] != '=')
		i++;
	var_name = ft_substr(line_tmp->args_built_in[1], 0, i);
	while (*env)
	{
		if (!ft_strncmp(var_name, (*env)->env, ft_strlen(var_name)))
		{
			value = ft_substr(line_tmp->args_built_in[1], i, ft_strlen(line_tmp->args_built_in[1]) - i);
			join = ft_strjoin(var_name, value,2);
			// free(tmp->env);
			(*env)->env = join;
		}
			printf("%s\n",(*env)->env);
		*env = (*env)->next;
	}
	*env = tmp;
	}
}