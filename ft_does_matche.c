/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_does_matche.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:32:36 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/17 15:09:51 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_str(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int    ft_search_back(char *pattern, char *text, int l, int ll)
{
    while (l >= 0 && ll >= 0)
    {
        if (pattern[l] == '*')
        {
            while (l > 0 && pattern[l] == '*')
                l--;
            if (l <= 0)
                return 1;
            while (text[ll] && text[ll] != pattern[l])
                ll--;
        }
        if (pattern[l] == text[ll])
        {
            l--;
            ll--;
        }
        else
            return 0;
    }
    if ((l <= 0 && ll <= 0) || pattern[0] == '*')
        return  (1);
    else
        return (0);
}

int ft_is_there_in_the_dir(char *pattern, char *text)
{
    int i;
    int j;
    int l;
    int ll;

    (1) && (i = 0, j = 0, l = ft_str(pattern) - 1, ll = ft_str(text) - 1);
    if (pattern[l] != '*')
        return (ft_search_back(pattern, text, l, ll));
    else
    {
        while (pattern[i] && text[j])
        {
            if (pattern[i] == '*')
            {
                while (pattern[i] == '*')
                    i++;
                if (pattern[i] == '\0')
                    return 1;
                while (text[j] && text[j] != pattern[i])
                    j++; 
            }
            if (pattern[i] == text[j])
                (1) && (i++, j++);
            else
                return 0;
        }
        return ((pattern[i] == '\0' && text[j] == '\0') || pattern[i] == '*');
    }
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
