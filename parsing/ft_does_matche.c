/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_matche.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:32:36 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/30 10:04:20 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_utils4(char *line, char *str, int j, int i)
{
	int	flag;

	while (line && line[i])
	{
		if (line[i] != '\'' && line[i] != '\"')
			(1) && (str[j] = line[i], j++);
		else if (line[i] == '\"' || line[i] == '\'')
		{
			(1) && (flag = line[i], i++);
			while (line[i])
			{
				if (line[i] == flag)
				{
					flag = 0;
					break ;
				}
				else if (line[i] != flag && line[i])
					(1) && (str[j] = line[i], j++);
				i++;
			}
		}
		if (line[i])
			i++;
	}
	return (str[j] = '\0', str);
}

char	*ft_remove3(char *line)
{
	int		j;
	int		count;
	char	*str;
	int		i;

	j = 0;
	str = NULL;
	i = 0;
	count = ft_remove_utils3(line);
	if (count > 0)
		str = malloc(count + 1 * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_remove_utils4(line, str, j, i);
	return (str);
}

int	ft_is_between_quotes(char *str)
{
	int	i;
	int	quote;
	int	flag;

	(1) && (i = 0, quote = 0, flag = 0);
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			(1) && (flag = 1, quote = str[i], i++);
		while (str[i] && flag == 1 && str[i] != quote)
		{
			if (str[i] == '*')
				return (1);
			i++;
		}
		if (flag == 1 && str[i] == quote)
			(1) && (flag = 0, quote = 0);
		i++;
	}
	return (0);
}

char	**ft_does_matche_utils(DIR *dir, struct dirent *name, char *str)
{
	int		i;
	char	**array;

	(1) && (i = 0, array = NULL);
	if (dir)
	{
		array = malloc(sizeof(char *) * 1000);
		name = readdir(dir);
		while (array && name != NULL)
		{
			if (ft_is_there_in_the_dir(str, name->d_name)
				&& name->d_name[0] != '.')
				(1) && (array[i] = ft_strdup(name->d_name), i++);
			name = readdir(dir);
		}
		if (array)
			array[i] = NULL;
		closedir(dir);
	}
	else
		perror("opendir");
	if (array)
		array[i] = NULL;
	return (array);
}

char	**ft_does_it_matche(char *str)
{
	int				i;
	DIR				*dir;
	struct dirent	*name;
	char			**array;
	char			*str1;

	(1) && (i = 0, name = NULL);
	if (ft_is_between_quotes(str))
	{
		str1 = ft_remove3(str);
		array = malloc(sizeof(char *) * 2);
		if (!array)
			return (NULL);
		array[0] = ft_strdup(str1);
		array[1] = NULL;
		return (array);
	}
	if (ft_strchr1(str, '\"') || ft_strchr1(str, '\''))
		str = ft_remove3(str);
	dir = opendir(".");
	array = ft_does_matche_utils(dir, name, str);
	if (array && ft_count_2d(array) == 0)
		(1) && (array[0] = ft_strdup(str), array[1] = NULL);
	return (array);
}
