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

void    ft_sort_list(t_env **env)
{
    t_env    *first;
    t_env    *second;
    char    *tmp;

    first = *env;
    while (first != NULL && first->next != NULL)
    {
        second = *env;
        while (second != NULL && second->next != NULL)
        {
            if (ft_strcmp_asd(second->env, second->next->env) > 0)
            {
                tmp = second->env;
                second->env = second->next->env;
                second->next->env = tmp;
            }
            second = second->next;
        }
        first = first->next;
    }
}

void declare_export(t_env *env)
{
	t_env *tmp;
	t_env *last_node;
	t_env *node;
	t_env *head = NULL;
	tmp = env;
	while (tmp)
	{
		node = malloc(sizeof(t_env));
		node->env = ft_strdup(tmp->env);
		node->next = NULL;		
		if (!head)
		{
			head = node;
		}
		else
		{
			last_node = get_last(&head);
			last_node->next = node;
		}
		tmp = tmp->next;
	}
	node = head;
	ft_sort_list(&head);
	while (head)
	{
		printf("declare -x %s\n",head->env);
		head = head->next;
	}
	// ft_free_env(&node);
}


void exec_export(t_holder **holder, t_env **env)
{
	int i;
	char *node_env;
	char *var_name;
	char *value;
	t_env *tmp;
	t_env *node;
	int is_invalid = 0;
	t_holder *line_tmp;
	char *join;
	int j;
	line_tmp = *holder;
	tmp = *env;
	if (!line_tmp->args_built_in[1])
	{
		declare_export(*env);
	}
	else
	{
	i = 0;
	j = 1;
	while(line_tmp->args_built_in[j])
	{
	if (line_tmp->args_built_in[j][0] && (line_tmp->args_built_in[j][0] >= '0' && line_tmp->args_built_in[j][0] <= '9'))
	{
		printf("bash: export: `%s': not a valid identifier\n",line_tmp->args_built_in[j]);
		j++;
		continue;
	}
	while (line_tmp->args_built_in[j][i] && line_tmp->args_built_in[j][i] != '=')
	{
		if (line_tmp->args_built_in[j][i] == '.' || line_tmp->args_built_in[j][i] == ',' ||
		 line_tmp->args_built_in[j][i] == '/' || line_tmp->args_built_in[j][i] == '-' || line_tmp->args_built_in[j][i] == ':')
		 {
			printf("bash: export: `%s' not a valid identifipper\n",line_tmp->args_built_in[j]);
			j++;
			i = 0;
			is_invalid = 1;
			break;
		 }
		i++;
	}
	if (is_invalid == 1)
	{
		is_invalid = 0;
		continue;
	}
	if (line_tmp->args_built_in[j][i] && line_tmp->args_built_in[j][i-1] == '+')
	{
	var_name = ft_substr(line_tmp->args_built_in[j], 0, i-1);
	while (*env)
	{
		if (!ft_strncmp(var_name, (*env)->env, ft_strlen(var_name)))
		{
			value = ft_substr(line_tmp->args_built_in[j], i+1, ft_strlen(line_tmp->args_built_in[j]) - i-1);
			// join = ft_strjoin(var_name, value,2);
			// free(tmp->env); 
			(*env)->env = ft_strjoin((*env)->env, value,2);
			free(var_name);
			break;
		}
		*env = (*env)->next;
	}
	}
	else
	{
	var_name = ft_substr(line_tmp->args_built_in[j], 0, i);
	while (*env)
	{
		if (!ft_strncmp(var_name, (*env)->env, ft_strlen(var_name)))
		{
			value = ft_substr(line_tmp->args_built_in[j], i, ft_strlen(line_tmp->args_built_in[j]) - i);
			join = ft_strjoin(var_name, value,2);
			// free(tmp->env); 
			(*env)->env = join;
			break;
		}
		*env = (*env)->next;
	}
	
	if (!(*env))
	{
	*env = tmp;
	while ((*env)->next)
	{
		(*env) = (*env)->next;
	}
		value = ft_substr(line_tmp->args_built_in[1], i, ft_strlen(line_tmp->args_built_in[1]) - i);
		join = ft_strjoin(var_name, value,2);
		node = malloc(sizeof(t_env));
		node->env = join;
		node->next = NULL;
		(*env)->next = node;
	}
	}
	j++;
	*env = tmp;
	i = 0;
	}
	}
	
}