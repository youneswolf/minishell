/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 01:53:45 by asedoun           #+#    #+#             */
/*   Updated: 2024/05/29 21:49:53 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_second_null_env(t_env **mini_env)
{
	char	buf[1024];
	char	*var;
	char	*final;
	t_env	*node;
	int		i;

	var = ft_strdup("PWD=");
	i = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
		perror("getcwd");
	node = malloc(sizeof(t_env));
	if (!node)
	{
		(ft_free_nodes(mini_env));
		return ;
	}
	final = ft_strjoin(var, buf, 1);
	node->env = final;
	node->deleted = 0;
	node->next = NULL;
	(*mini_env)->next = node;
}

void	ft_free_nodes(t_env **a)
{
	t_env	*head;
	t_env	*tobefreed;

	head = *a;
	while (head != NULL)
	{
		tobefreed = head;
		head = head->next;
		free(tobefreed);
	}
	*a = NULL;
}

void	fill_env(t_env **mini_env, char **env)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		line = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!line)
			return ;
		while (env[i][j])
		{
			line[j] = env[i][j];
			j++;
		}
		line[j] = '\0';
		env_list(mini_env, line);
		i++;
	}
}

int	check_is_closed(char *str, int sgl)
{
	int	i;
	int	j;
	int	k;
	int	count;

	count = 0;
	k = 0;
	j = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
		{
			j = 1;
			count++;
		}
		if (j && (str[i] == '$' || (sgl && str[i] == '$')))
			k = 1;
		i++;
	}
	if (k && count % 2 == 1)
		return (1);
	return (0);
}

int	check_sgl_parity(char *str, int i, int sgl)
{
	int	parity;

	sgl += count_sgl(str, i);
	parity = sgl / 2;
	if (sgl % 2 == 0 && sgl != 0 && parity % 2 == 1 
		&& check_is_closed(str, sgl))
		return (1);
	return (0);
}
