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
			break;
		}
		*env = (*env)->next;
	}
	*env = tmp;
	}
}