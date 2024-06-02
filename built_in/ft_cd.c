/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/30 10:05:35 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_utils(t_env **mini_env, char *str1, char *str)
{
	t_env	*tmp;

	tmp = *mini_env;
	while (*mini_env)
	{
		if ((*mini_env)->env && f_strcmp((*mini_env)->env, "PWD"))
		{
			if ((*mini_env)->deleted == 1)
			{
				*mini_env = (*mini_env)->next;
				continue ;
			}
			perror("error retrieving current directory: getcwd: cannot access \
			parent directories: ");
			ft_status(1, 0);
			str1 = ft_strjoin((*mini_env)->env, "/", 1);
			str1 = ft_strjoin(str1, str, 1);
			(*mini_env)->env = ft_strdup(str1);
			free(str1);
			break ;
		}
		*mini_env = (*mini_env)->next;
	}
	*mini_env = tmp;
}

void	ft_cd_utils_1(t_env **mini_env, char *str1, char *str)
{
	t_env	*tmp;

	tmp = *mini_env;
	while (*mini_env)
	{
		if (mini_env && (*mini_env)->env && f_strcmp((*mini_env)->env, "PWD"))
		{
			if ((*mini_env)->deleted == 1)
			{
				*mini_env = (*mini_env)->next;
				continue ;
			}
			str1 = ft_strjoin((*mini_env)->env, "/", 1);
			str1 = ft_strjoin(str1, str, 1);
			(*mini_env)->env = ft_strdup(str1);
			free(str1);
			break ;
		}
		*mini_env = (*mini_env)->next;
	}
	*mini_env = tmp;
}

int	ft_cd(char *str, t_env **mini_env)
{
	char	buf[PATH_MAX];
	char	*str1;
	DIR		*dir;
	char	curdir[PATH_MAX];

	str1 = NULL;
	dir = opendir(str);
	if (dir == NULL)
		return (ft_status(1, 1), perror("path not found"), 0);
	if (getcwd(curdir, sizeof curdir))
		*curdir = '\0';
	if (str == NULL || str[0] == '\0')
		str = getenv("HOME");
	else if (chdir(str) == 0)
	{
		closedir(dir);
		if (getcwd(buf, sizeof(buf)) != NULL)
			ft_cd_utils_1(mini_env, str1, str);
		else
			ft_cd_utils(mini_env, str1, str);
		ft_status(1, 0);
	}
	else
		perror("directory not found");
	return (ft_status(1, 0), 1);
}
