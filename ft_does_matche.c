/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_matche.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:32:36 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/16 14:46:13 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_there_in_the_dir(char *str, char *s1)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str && s1 && str[i] && s1[j])
    {
        if (str[i] == '*')
        {
            while (str[i] && str[i] == '*')
                i++;
            if (str[i] == '\0')
                return (1);
        }
        while (s1 && s1[j])
        {
            if (str[i] == s1[j])
            {
                j++;
                i++;
            }
            else if (str[i] == '*')
            {
                j++;
                break;
            }
            else if (str[i] != s1[j])
                return (0);
            else
                j++;
        }
        if (s1[j] == '\0')
            return (0);
        i++;
    }
    return (1);
}

int ft_is_there(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '*')
            return (1);
        i++;
    }
    return (0);
}

char **ft_does_it_matche(char *str)
{
    int             i;
    DIR*            dir;
    struct dirent   *name;
    char            **array;

    i = 0;
    dir = opendir(".");
    if (dir)
    {
        array = malloc(sizeof(char *) * 1000);
        name = readdir(dir);
        while (name != NULL)
        {
            if (ft_is_there_in_the_dir(str, name->d_name) && name->d_name[0] != '.')
            {
                array[i] = ft_strdup(name->d_name);
                printf("{%s}\n", array[i]);
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
