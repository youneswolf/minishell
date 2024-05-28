/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:49:23 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 02:13:51 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

t_env	*get_last(t_env **a)
{
	t_env	*tmp;

	if (!(*a)->next)
		return (*a);
	tmp = *a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_free1(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

t_line	*get_last_l(t_line **a)
{
	t_line	*tmp;

	if (!(*a)->next)
		return (*a);
	tmp = *a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_strjoin(char *static_str, char *buff, int is_free)
{
	t_join	vars;

	if (!static_str && !buff)
		return (ft_strdup(""));
	vars.len = ft_strlen(static_str);
	vars.str = malloc(sizeof(char) * (vars.len + ft_strlen(buff)) + 1);
	if (!vars.str)
		return (ft_free1(&static_str));
	vars.i = 0;
	vars.j = 0;
	while (static_str && static_str[vars.i] != '\0')
	{
		vars.str[vars.i] = static_str[vars.i];
		vars.i++;
	}
	while (buff && buff[vars.j] != '\0')
		vars.str[vars.i++] = buff[vars.j++];
	vars.str[vars.i] = '\0';
	if (is_free == 1)
		free(static_str);
	else if (is_free == 2)
		(free(static_str), free(buff));
	else if (is_free == 3)
		free(buff);
	return (vars.str);
}
