/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:38:00 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 22:32:47 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cd(char *str, t_env *mini_env)
{
    char buf[PATH_MAX];

    char curdir[PATH_MAX];
    static char lastdir[PATH_MAX];
    char path[PATH_MAX];

    int i = 0;
    while (mini_env)
    {
        printf("%s\n", mini_env->env);
        mini_env = mini_env->next;
    }
    if (getcwd(curdir, sizeof curdir)) {
        /* current directory might be unreachable: not an error */
        *curdir = '\0';
    }
    if (str == NULL)
        str = getenv("HOME");
    else {
        /* this should be done on all words during the parse phase */
        if (*str == '~') {
            if (str[1] == '/' || str[1] == '\0') {
                str = ft_strjoin(getenv("HOME"), str + 1);
            } else {
                /* ~name should expand to the home directory of user with login `name` 
                   this can be implemented with getpwent() */
                printf("syntax not supported:\n");
                return 1;
            }
        }
    }
    if (chdir(str) == 0)
    {
        // Get the current working directory
        if (getcwd(buf, sizeof(buf)) != NULL) {
            printf("Current working directory:%s\n", buf);
        } else {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
    }
    else 
        perror("directory not found");
    strcpy(lastdir, curdir);
    return(1);
}