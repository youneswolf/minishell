/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:48:36 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 04:43:04 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_status_str(char *str, int i, int status_int)
{
	char	*status_str_pre;
	char	*status_str_after;
	char	*status;

	if (status_int == 1337)
		status = ft_itoa(ft_status(0, 1337));
	else
		status = ft_itoa(status_int);
	status_str_pre = ft_sub_str(str, 0, i - 1, 0);
	if (!status_str_pre)
		perror("malloc_error");
	status_str_after = ft_sub_str(str, i + 2, ft_strlen(str) - i - 2, 0);
	if (!status_str_after)
		perror("malloc_error");
	status = ft_strjoin(status_str_pre, status, 2);
	status = ft_strjoin(status, status_str_after, 2);
	free(str);
	return (status);
}

char	*put_status_in_str(char *str, int status_int)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			str = get_status_str(str, i + 1, status_int);
		}
		i++;
	}
	return (str);
}

char	*find_path(t_env *env)
{
	char	*dest; 
	t_env	*tmp;

	dest = NULL;
	tmp = env;
	dest = NULL;
	while (tmp)
	{
		if (tmp->deleted != 1)
		{
			dest = strnstr(tmp->env, "PATH=", 5);
			if (dest)
				break ;
		}
		tmp = tmp->next;
	}
	return (dest);
}

char	*skip_path(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) - 4);
	if (!new_str)
		return (NULL);
	while (str[i] && i < 5)
		i++;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free (str);
	return (new_str);
}

char	*ft_strjoin_path(char *static_str, char *buff)
{
	t_join	vars;

	if (!static_str && !buff)
		return (NULL);
	if (!static_str && buff)
		return (ft_strdup(buff));
	if (!buff && static_str)
		return (ft_strdup(static_str));
	vars.len = ft_strlen(static_str);
	vars.str = malloc(sizeof(char) * (vars.len + ft_strlen(buff)) + 2);
	if (!vars.str)
		exit(1);
	vars.i = 0;
	vars.j = 0;
	while (static_str && static_str[vars.i] != '\0')
	{
		vars.str[vars.i] = static_str[vars.i];
		vars.i++;
	}
	(1) && (vars.str[vars.i] = '/', vars.i++);
	while (buff && buff[vars.j] != '\0')
		vars.str[vars.i++] = buff[vars.j++];
	vars.str[vars.i] = '\0';
	free(static_str);
	return (vars.str);
}
