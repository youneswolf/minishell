/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:00:44 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/06 15:35:33 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) *(i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int ft_check_if_chars_digit(char c)
{
    return ((c >= '0' && c <= '9')||(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*ft_strchr(const char *s, int c)
{
	char	x;
	int		i;

	i = 0;
	x = (char)c;
	while (s[i])
	{
		if (s[i] == x)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == x)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}


char	*ft_allocate_for_var(int flag, char *str, int i)
{
	char	*ptr;

	ptr = NULL;
	if (flag == 1 && str != NULL)
	{
		str += (i + 1);
		ptr = ft_strdup(str);
		if (!ptr)
			return (NULL);
		str -= (i + 1);
		return (ptr);
	}
	return (ptr);
}

char	*ft_arg_is_exist(t_env *env, char *var)
{
	t_env	*head;
	char	*ptr = NULL;
	int		i;
	int		flag;

	(1) && (head = env, i = 0, flag = 0);
	while (head != NULL)
	{
		i = 0;
		while (var[i] == head->value[i])
			i++;
		if (head->value[i] == '=' && !ft_check_if_chars_digit(var[i]))
		{
			flag = 1;
			break ;
		}
		head = head->next;
	}
    if (head)
	    ptr = ft_allocate_for_var(flag, head->value, i);
    if (!ptr)
        return (NULL);
	return (ptr);
}

int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

void	ft_append_char(char **str, int c)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	s = *str;
	*str = malloc(sizeof(char) * (len + 2));
	if (!(*str))
		return ;
	while (s && s[i])
	{
		(*str)[i] = s[i];
		i++;
	}
	(1) && ((*str)[i++] = c, (*str)[i] = '\0');
	free(s);
}

char	*ft_handle_expand(t_env *env, char *arg)
{
	int		i;
	int		quote;
	char	*expa;
	char	*new_str;
	char	*s;

	(1) && (new_str = NULL, i = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		quote = arg[i++];
	while (arg[i] != '\0')
	{
		if (arg[i] == quote)
			i++;
		if (!arg[i])
			break ;
		if ((arg[i] == '$' || arg[i] == '\"') && quote != '\'')
		{
			expa = ft_arg_is_exist(env, arg + (i + 1));
			s = new_str;
			new_str = ft_strjoin(new_str, expa);
			i += ft_surpass_chars(arg + (i + 1));
		}
		else
			ft_append_char(&new_str, arg[i++]);
		if (arg[i] == '\0')
			break ;
	}
	return (new_str);
}

void	ft_expand_argument(t_env *env, t_line **linked_list)
{
	t_line	*head;

	head = *linked_list;
	while (head != NULL)
	{
		if (ft_strchr(head->str, '$'))
			head->str = ft_handle_expand(env, head->str);
		head = head->next;
	}
}
