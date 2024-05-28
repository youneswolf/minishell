/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:49:16 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/28 04:45:43 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(t_env *env, char *cmd)
{
	int		k;
	int		i;
	char	**path;

	i = -1;
	path = ft_split(find_path(env), ':');
	if (!path)
		return (NULL);
	path[0] = skip_path(path[0]);
	while (cmd && path[++i])
		path[i] = ft_strjoin_path(path[i], cmd);
	i = 0;
	while (path && path[i])
	{
		if (access(path[i], X_OK) == 0)
			break ;
		free(path[i++]);
	}
	if (!path[i])
		return (NULL);
	k = i + 1;
	while (path[k] && path)
		free(path[k++]);
	return (path[i]);
}

char	**ft_put_env_string(char **array, t_env *env)
{
	int		i;
	t_env	*tmp;
	int		l;

	l = 0;
	tmp = env;
	i = 0;
	while (tmp)
	{
		l++;
		tmp = tmp->next;
	}
	tmp = env;
	array = malloc((l + 1) * sizeof(char *));
	while (tmp)
	{
		array[i] = ft_strdup(tmp->env);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

int	is_slash(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
