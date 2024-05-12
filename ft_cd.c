/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/12 19:23:55 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd_utils(t_env **mini_env, char *str1, char *str)
{
    char *str2;

    while(mini_env)
    {
        if (f_strcmp((*mini_env)->env, "PWD"))
        {
            perror("error retrieving current directory: getcwd: cannot access parent directories: ");
            str1 = ft_strjoin((*mini_env)->env, "/", 1);
            str1 = ft_strjoin((*mini_env)->env, str, 1);
            (*mini_env)->env = ft_strdup(str1);
            free(str1);
            break;
        }
        *mini_env = (*mini_env)->next;
    }
}

int    ft_cd(char *str, t_env **mini_env)
{
    char buf[PATH_MAX];
    char    *str1;
    DIR    *dir;
    char curdir[PATH_MAX];
    char path[PATH_MAX];

    int i = 0;
    dir = opendir(str);
    if (dir == NULL)
    {
        perror("path not found");
        return (0);
    }
    if (getcwd(curdir, sizeof curdir))
        *curdir = '\0';
    if (str == NULL || str[0] == '\0')
        str = getenv("HOME");
    else if (chdir(str) == 0)
    {
        closedir(dir);
        if (getcwd(buf, sizeof(buf)) != NULL)
        {
            while (mini_env)
            {
                if (f_strcmp((*mini_env)->env, "PWD"))
                {
                    str1 = ft_strjoin((*mini_env)->env, "/", 1);
                    str1 = ft_strjoin(str1, str, 1);
                    (*mini_env)->env = ft_strdup(str1);
                    free(str1);
                    break;
                }
                *mini_env = (*mini_env)->next;
            }
        }
        else
        {
            // ft_cd_utils(mini_env, str1, str);
            while(mini_env)
            {
                if (f_strcmp((*mini_env)->env, "PWD"))
                {
                    perror("error retrieving current directory: getcwd: cannot access parent directories: ");
                    str1 = ft_strjoin((*mini_env)->env, "/", 1);
                    str1 = ft_strjoin(str1, str, 1);
                    (*mini_env)->env = ft_strdup(str1);
                    free(str1);
                    break;
                }
                *mini_env = (*mini_env)->next;
            }
        }
    }
    else
        perror("directory not found");
    return(1);
}
