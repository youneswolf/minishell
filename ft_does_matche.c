/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_matche.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:32:36 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/22 11:10:54 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 1)
		return (2);
	return (i - 1);
}

int	ft_search_back(char *pattern, char *text, int l, int ll)
{
	while (l >= 0 && ll >= 0)
	{
		if (pattern[l] == '*')
		{
			while (l > 0 && pattern[l] == '*')
				l--;
			if (l <= 0)
				return (1);
			while (text[ll] && text[ll] != pattern[l])
				ll--;
		}
		if (pattern[l] == text[ll])
		{
			l--;
			ll--;
		}
		else
			return (0);
	}
	if ((l <= 0 && ll <= 0) || pattern[0] == '*')
		return (1);
	else
		return (0);
}

int	ft_is_there_in_the_dir(char *pattern, char *text)
{
	t_does_match	t;

	(1) && (t.i = 0, t.j = 0, t.l = ft_str(pattern), t.ll = ft_str(text));
	if (pattern && pattern[t.l - 1] == '*')
		return (ft_search_back(pattern, text, t.l, t.ll));
	else
	{
		while (pattern[t.i] && text[t.j])
		{
			if (pattern[t.i] == '*')
			{
				while (pattern[t.i] == '*')
					t.i++;
				if (pattern[t.i] == '\0')
					return (1);
				while (text[t.j] && text[t.j] != pattern[t.i])
					t.j++;
			}
			if (pattern[t.i] && pattern[t.i] == text[t.j])
				(1) && (t.i++, t.j++);
			else
				return (0);
		}
		return ((pattern[t.i] == text[t.j] == '\0') || pattern[t.i] == '*');
	}
}

int	ft_is_there(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

int	ft_remove_utils3(char *str)
{
	int	count;
	int	flag;
	int	i;

	count = ft_strlen(str);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			(1) && (flag = str[i], i++);
			while (str[i])
			{
				if (str[i] == flag)
				{
					(1) && (count -= 2, flag = 0);
					break ;
				}
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (count + 1);
}

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

	i = 0;
	if (dir)
	{
		array = malloc(sizeof(char *) * 1000);
		name = readdir(dir);
		while (name != NULL)
		{
			if (ft_is_there_in_the_dir(str, name->d_name)
				&& name->d_name[0] != '.')
			{
				array[i] = ft_strdup(name->d_name);
				i++;
			}
			name = readdir(dir);
		}
		array[i] = NULL;
		closedir(dir);
	}
	else
		perror("opendir");
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

	i = 0;
	if (ft_is_between_quotes(str))
	{
		str1 = ft_remove3(str);
		array = malloc(sizeof(char *) * 2);
		array[0] = str1;
		array[1] = NULL;
		return (array);
	}
	if (ft_strchr1(str, '\"') || ft_strchr1(str, '\''))
		str = ft_remove3(str);
	dir = opendir(".");
	array = ft_does_matche_utils(dir, name, str);
	if (ft_count_2d(array) == 0)
	{
		array[0] = str;
		array[1] = NULL;
	}
	return (array);
}
