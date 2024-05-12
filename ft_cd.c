/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/08 12:06:30 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int     ft_cd_utils(char *str)
// {
//     DIR    *dir;

//     dir = opendir(str);
//     if (dir == NULL)
//     {
//         perror("path not found");
//         return (0);
//     }
// }

int    ft_cd(char *str, t_env **mini_env) //, t_line *head
{
    char buf[PATH_MAX];
    char    *str1;
    DIR    *dir;
    char curdir[PATH_MAX];
    // static char lastdir[PATH_MAX];
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
        /* current directory might be unreachable: not an error */
    if (str == NULL || str[0] == '\0')
        str = getenv("HOME");
    else if (chdir(str) == 0)
    {
        // Get the current working directory
        closedir(dir);
        if (getcwd(buf, sizeof(buf)) != NULL)
        {
            while (mini_env)
            {
                if (f_strcmp((*mini_env)->env, "PWD"))
                {
                    str1 = ft_strjoin((*mini_env)->env, "/", 1);
                    str1 = ft_strjoin(str1, str, 1);
                    // free((*mini_env)->env);
                    (*mini_env)->env = ft_strdup(str1);
                    free(str1);
                    break;
                }
                *mini_env = (*mini_env)->next;
            }
        }
        else
        {
            while(mini_env)
            {
                if (f_strcmp((*mini_env)->env, "PWD"))
                {
                    perror("error retrieving current directory: getcwd: cannot access parent directories: ");
                    str1 = ft_strjoin((*mini_env)->env, str, 1);
                    // str1 = ft_strjoin(str1, str, 1);
                    // free((*mini_env)->env);
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
    // head->status1->lastdir = ft_strdup(buf);
    return(1);
}
