/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matche_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:31:35 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 17:47:58 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_is_there_in_the_dir(char *pat, char *text)
{
	t_does_match	t;

	(1) && (t.i = 0, t.j = 0, t.l = ft_str(pat), t.ll = ft_str(text));
	if (pat && pat[t.l - 1] == '*')
		return (ft_search_back(pat, text, t.l, t.ll));
	else if (pat)
	{
		while (pat && pat[t.i] && text[t.j])
		{
			if (pat[t.i] == '*')
			{
				ft_uttt(&t, pat, text, 0);
				if (pat[t.i] == '\0')
					return (1);
				ft_uttt(&t, pat, text, 1);
			}
			if (pat[t.i] && text[t.j] && pat[t.i] == text[t.j])
				(1) && (t.i++, t.j++);
			else
				return (0);
		}
		return ((pat[t.i] == '\0' && text[t.j] == '\0') || pat[t.i] == '*');
	}
	return (0);
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
