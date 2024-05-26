/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:51:51 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 13:53:43 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_there_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'e' && str[i+1] == 'x' && str[i+2] == 'i' && str[i+3] == 't')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_space_utils(char *new_line, char *str, int quote, int i, int j)
{
	int	flag;

	flag = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			(1) && (flag = 1, quote = str[i]);
		if (flag == 0 && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
		{
			(1) && ( new_line[j] = ' ', new_line[j + 1] = str[i]);
			(1) && (new_line[j + 2] = str[i], new_line[j + 3] = ' ');
			(1) && (j = j + 3, i++);
		}
		else if (flag == 0 && (str[i] == '|' || str[i] == '>' || str[i] == '<'))
		{
			(1) && (new_line[j] = ' ', new_line[j + 1] = str[i]);
			(1) && (new_line[j + 2] = ' ', j = j + 2);
		}
		else
			new_line[j] = str[i];
		(1) && (i++, j++);
		if (str[i] && str[i] == quote)
			(1) && (new_line[j] = str[i], i++, j++, flag = 0, quote = 0);
	}
	new_line[j] = '\0';
}

char    *ft_add_space_to_command(char *str)
{
	int 	i;
	char 	*new_line;
	int		count;
	int		quote;

	(1) && (i = 0, count = 0, quote = 0); 
	while (str && str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<'
		|| (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				count++;
			i++;
	}
	new_line = malloc(i + 1 + count * 2);
	if (!new_line)
		return (free(str), perror("malloc"), NULL);
	i = 0;
	count = 0;
	ft_add_space_utils(new_line, str, quote, i, count);
	return (free(str), new_line);
}

char    *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t    i;
    size_t    j;
    char    *src;

    src = (char *)haystack;
    j = 0;
    i = 0;
    if (needle[0] == '\0')
    {
        return (src);
    }
    while (i < len && haystack[i])
    {
        j = 0;
        while (haystack[i + j] == needle[j] && (i + j) < len)
        {
            if (needle[j + 1] == '\0')
            {
                return (&src[i]);
            }
            j++;
        }
        i++;
    }
    return (NULL);
}
