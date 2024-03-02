/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/02 14:38:10 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <string.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#define CMD "cmd"
#define PIPE "pipe"
#define ARGS "args"
#define IN_REDIR "in_redir"
#define OUT_REDIR "out_redir"
typedef struct s_line
{
    char *str;
    char *token;
    struct s_line *next;
}t_line;
void    ft_pwd();
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int	count(const char *s, char c);
char	*word(const char *str, char c);
int	ft_free(char **array, const char *str, char c, int a);
char	**alloc(int l);
char	**ft_split(const char *str, char c);
int    ft_cd(char *str);
#endif