/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:32:00 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/11 16:32:42 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_export(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], 1);
		if (s[i] == '=')
		{
			j = 1;
			write(1, "\"", 1);
		}
		i++;
	}
	if (j)
		write(1, "\"", 1);
}

int	check_is_all_printed(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->printed == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_sort_list(t_env **env)
{
	t_env	*first;
	t_env	*second;
	char	*tmp;

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
void	ft_print_export(t_env *head)
{
	while (head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_export(head->env);
		write(1, "\n", 1);
		head = head->next;
	}
}

void    ft_free_env(t_env **str)
{
	t_env *to_be_free;
	t_env	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->env);
		free(prev);
	}
}

void	exec_fcts(t_env *head, t_env *node)
{
	ft_sort_list(&head);
	ft_print_export(head);
	ft_free_env(&node);
} 

void	declare_export(t_env *env)
{
	t_env	*tmp;
	t_env	*last_node;
	t_env	*node;
	t_env	*head;

	head = NULL;
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
	exec_fcts(head, node);
}

char	*ft_add_quotes(char *str)
{
	int	i;
	int	j;
		char *new_value;

	if (str)
	{
		i = 1;
		j = 2;
		new_value = malloc(ft_strlen(str) + 3);
		if (!new_value)
			return (NULL);
		new_value[0] = '=';
		new_value[1] = 34;
		while (str && str[i] && str[i] != '=')
		{
			new_value[j] = str[i];
			i++;
			j++;
		}
		new_value[j++] = 34;
		new_value[j] = '\0';
		free(str);
		return (new_value);
	}
	return (str);
}

void	if_not_in_env(t_export *vars, t_env **env)
{
	*env = vars->tmp;
	while ((*env)->next)
	{
		(*env) = (*env)->next;
	}
	vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j], vars->i,
		ft_strlen(vars->line_tmp->args_built_in[vars->j]) - vars->i);
	vars->join = ft_strjoin(vars->var_name, vars->value, 2);
	vars->node = malloc(sizeof(t_env));
	vars->node->env = vars->join;
	vars->node->next = NULL;
	(*env)->next = vars->node;
}

void	if_not_in_env1(t_export *vars, t_env **env)
{
	*env = vars->tmp;
	while ((*env)->next)
	{
		(*env) = (*env)->next;
	}
	vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j], vars->i,
		ft_strlen(vars->line_tmp->args_built_in[vars->j]) - vars->i);
	vars->join = ft_strjoin(vars->var_name, vars->value, 2);
	vars->node = malloc(sizeof(t_env));
	vars->node->env = vars->join;
	vars->node->next = NULL;
	(*env)->next = vars->node;
	vars->j++;
}

void	add_vars(t_export *vars, t_env **env)
{
	vars->var_name = ft_substr(vars->line_tmp->args_built_in[vars->j], 0,
		vars->i);
	while (*env)
	{
		if (!ft_strncmp(vars->var_name, (*env)->env, ft_strlen(vars->var_name)))
		{
			vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j],
				vars->i, ft_strlen(vars->line_tmp->args_built_in[vars->j])
				- vars->i);
			vars->join = ft_strjoin(vars->var_name, vars->value, 2);
			free((*env)->env);
			(*env)->env = vars->join;
			break ;
		}
		*env = (*env)->next;
	}
	if (!(*env))
		if_not_in_env(vars, env);
	vars->j++;
	*env = vars->tmp;
	vars->i = 0;
}
void print_error(t_export *vars)
{
	printf("bash: export: `%s' not a valid identifier\n",
		vars->line_tmp->args_built_in[vars->j]);
	vars->j++;
	vars->i = 0;
	vars->is_invalid = 1;
}
void	check_validity(t_export *vars, t_env **env)
{
	if (vars->i == 0 &&  (vars->line_tmp->args_built_in[vars->j][vars->i] == '='))
	{
		print_error(vars);
	}
	else
	{
	while (vars->line_tmp->args_built_in[vars->j][vars->i]
		&& vars->line_tmp->args_built_in[vars->j][vars->i] != '=')
	{
		if (vars->line_tmp->args_built_in[vars->j][vars->i] == '.'
			|| vars->line_tmp->args_built_in[vars->j][vars->i] == ','
			|| vars->line_tmp->args_built_in[vars->j][vars->i] == '/'
			|| vars->line_tmp->args_built_in[vars->j][vars->i] == '-'
			|| vars->line_tmp->args_built_in[vars->j][vars->i] == ':')
		{
			print_error(vars);
			break ;
		}
		vars->i++;
	}
	}
}

void	put_env_value(t_export *vars, t_env **env)
{
	int	i;

	i = 1;
	vars->var_name = ft_substr(vars->line_tmp->args_built_in[vars->j], 0,
		vars->i - 1);
	while (*env)
	{
		if (!ft_strncmp(vars->var_name, (*env)->env, ft_strlen(vars->var_name)))
		{
			vars->value = ft_substr(vars->line_tmp->args_built_in[vars->j],
				vars->i + 1, ft_strlen(vars->line_tmp->args_built_in[vars->j])
				- vars->i - 1);
			(*env)->env = ft_strjoin((*env)->env, vars->value, 2);
			free(vars->var_name);
			i = 0;
			break ;
		}
		(*env) = (*env)->next;
	}
	if (i)
	{
		if_not_in_env1(vars, env);
	}
	else
		vars->j++;
}

void	export_vars(t_export *vars, t_holder **holder, t_env **env)
{
	vars->is_invalid = 0;
	vars->line_tmp = *holder;
	vars->tmp = *env;
	vars->i = 0;
	vars->j = 1;
}

int	check_first_is_nbr(char *str)
{
	if (str[0] && str[0] >= '0' && str[0] <= '9')
		return (0);
	return (1);
}

void	check_first_is_nbr2(t_export *vars)
{
	printf("bash: export: `%s': not a valid identifier\n",
		vars->line_tmp->args_built_in[vars->j]);
	vars->j++;
}

int	check_if_addition(char **str, t_export *vars)
{
	if (str && vars->i != 0 &&str[vars->j][vars->i - 1] == '+')
		return (1);
	return (0);
}
void check_env_vars(t_export *vars, t_env **env)
{
	if (check_if_addition(vars->line_tmp->args_built_in, vars))
		put_env_value(vars, env);
	else
		add_vars(vars, env);
}
void	exec_export(t_holder **holder, t_env **env)
{
	t_export	vars;

	export_vars(&vars, holder, env);
	if (!vars.line_tmp->args_built_in[1])
		declare_export(*env);
	else
	{
		while (vars.line_tmp->args_built_in[vars.j])
		{
			if (!check_first_is_nbr(vars.line_tmp->args_built_in[vars.j]))
			{
				check_first_is_nbr2(&vars);
				continue ;
			}
			check_validity(&vars, env);
			if (vars.is_invalid == 1)
			{
				vars.is_invalid = 0;
				continue ;
			}
			check_env_vars(&vars, env);
		}
	}
}