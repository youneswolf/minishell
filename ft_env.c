/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:00:08 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 22:33:21 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_t_env_len(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

static t_env	*ft_last_node(t_env *top)
{
	while (top->next)
		top = top->next;
	return (top);
}

static t_env	*ft_new_node(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	ft_push_value(char *value, t_env **head)
{
	t_env	*newnode;
	t_env	*last;

	newnode = ft_new_node(value);
	if (!newnode)
		return (0);
	if (!head || !(*head))
		*head = newnode;
	else
	{
		last = ft_last_node(*head);
		last->next = newnode;
	}
	return (1);
}

void	ft_free_env(t_env **head)
{
	t_env	*current;

	while (*head)
	{
		free((*head)->value);
		(*head)->value = NULL;
		current = *head;
		*head = (*head)->next;
		free(current);
	}
}

static t_env    *ft_create_new_env(void)
{
    t_env    *envp;
    char    pwd[PATH_MAX];
    char    *tmp;

    envp = NULL;
    if (ft_push_value("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", \
        &envp) == 0)
        return (NULL);
    tmp = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
    if (!tmp)
        (write(2, "Error: Allocation failed\n", 19), exit(1));
    if (ft_push_value(tmp, &envp) == 0)
        return (NULL);
    (free(tmp), tmp = NULL);
    return (envp);
}

t_env    *ft_get_env(char **env)
{
    t_env    *envp;

    envp = NULL;
    if (*env == NULL || env == NULL)
        envp = ft_create_new_env();
    else
    {
        while (*env)
        {
            if (ft_push_value(*env, &envp) == 0)
                return (NULL);
            env++;
        }
    }
    return (envp);
}