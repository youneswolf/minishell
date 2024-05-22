/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:39:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/22 12:28:23 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strccmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1 && str2 && (str1[i] == str2[i]))
		i++;
	if (str1 && str2 && (str1[i] == '\0' || str2[i] == '\0'))
		return (1);
	return (0);
}

void	ft_pwd(t_env *mini_env)
{
	char	buf[1024];
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = mini_env;
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("Current working directory:%s\n", buf);
	else
	{
		while (tmp)
		{
			if (ft_strccmp(tmp->env, "PWD"))
			{
				printf("%s\n", &tmp->env[4]);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
