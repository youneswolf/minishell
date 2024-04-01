/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/31 00:43:42 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int f_strcmp(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1 && str2 && str2[i] != '\0' && str1[i] != '\0')
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
}

int    ft_cd(char *str, t_env *mini_env)
{
    char buf[PATH_MAX];
    char    *str1;
    char curdir[PATH_MAX];
    static char lastdir[PATH_MAX];
    char path[PATH_MAX];

    int i = 0;
    if (getcwd(curdir, sizeof curdir)) {
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
    if (str == NULL || str[0] == '\0')
        str = getenv("HOME");
    else if (chdir(str) == 0)
    {
        // Get the current working directory
        if (getcwd(buf, sizeof(buf)) != NULL)
        {
            while (mini_env)
            {
                if (f_strcmp(mini_env->value, "PWD"))
                {
                    str1 = ft_strjoin(mini_env->value, "/");
                    str1 = ft_strjoin(str1, str);
                    mini_env->value = ft_strdup(str1);
                    // free(str1);
                    break;
                }
                mini_env = mini_env->next;
            }
            printf("Current working directory:%s\n", buf);
        } else {
            while(mini_env)
            {
                if (f_strcmp(mini_env->value, "PWD"))
                {
                    str1 = ft_strjoin(mini_env->value, "/");
                    str1 = ft_strjoin(str1, str);
                    mini_env->value = ft_strdup(str1);
                    printf("%s\n", mini_env->value);
                    // free(str1);
                    break;
                }
                mini_env = mini_env->next;
            }
        }
    }
    else
        perror("directory not found");
    strcpy(lastdir, curdir);
    return(1);
}
