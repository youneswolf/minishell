/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/01 15:04:33 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int f_strcmp(char *str1, char *str2)
// {
//     int i;

//     i = 0;
//     while (str1 && str2 && str2[i] != '\0' && str1[i] != '\0')
//     {
//         if (str1[i] != str2[i])
//             return (0);
//         i++;
//     }
//     return (1);
// }

int    ft_cd(char *str, t_env *mini_env, t_line *head)
{
    char buf[PATH_MAX];
    char    *str1;
    DIR    *dir;
    char curdir[PATH_MAX];
    // static char lastdir[PATH_MAX];
    char path[PATH_MAX];

    int i = 0;
    dir = opendir(str);
    printf("------%s----\n", str);
    if (dir == NULL)
    {
        perror("path not found");
        return (0);
    }
    if (getcwd(curdir, sizeof curdir)) {
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
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
                if (f_strcmp(mini_env->env, "PWD"))
                {
                    str1 = ft_strjoin(mini_env->env, "/", 1);
                    str1 = ft_strjoin(str1, str, 1);
                    mini_env->env = ft_strdup(str1);
                    // free(str1);
                    break;
                }
                mini_env = mini_env->next;
            }
            printf("Current working directory:%s\n", buf);
        }
        else
        {
            while(mini_env)
            {
                if (f_strcmp(mini_env->env, "PWD"))
                {
                    perror("error retrieving current directory: getcwd: cannot access parent directories: ");
                    str1 = ft_strjoin(mini_env->env, "/", 1);
                    str1 = ft_strjoin(str1, str, 1);
                    mini_env->env = ft_strdup(str1);
                    // printf("%s\n", mini_env->env);
                    // free(str1);
                    break;
                }
                mini_env = mini_env->next;
            }
        }
    }
    else
        perror("directory not found");
    // head->status->lastdir = ft_strdup(buf);
    return(1);
}
