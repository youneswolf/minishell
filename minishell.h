/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/04 18:39:49 by ybellakr         ###   ########.fr       */
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
#define CMD 0
#define PIPE 1
#define ARGS 2
#define IN_REDIR 3
#define OUT_REDIR 4
#define HERDOC 5
#define OUT_FILE 6
#define IN_FILE 7
#define FILE 8
#define APPEND 10
#define DELIMITER 11
# define GREEN        "\x1b[32m"
# define YELLOW        "\x1b[33m"
# define RED        "\x1b[31m"
# define BLUE        "\x1b[34m"
# define MAGENTA    "\x1b[35m"
# define CYAN        "\x1b[36m"
# define WHT        "\e[0;37m"
# define RESET        "\x1b[0m"
typedef struct s_line
{
    char *str;
    int token;
    struct s_line *next;
}t_line;
typedef struct s_env
{
    char *env;
    struct s_env *next;
}t_env;
void    ft_pwd();
void    ft_give_token(t_line *head);
static int ft_strcmp(char *str, char *str1);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int	count(char *s, char c);
char	*word(char *str, char c);
int	ft_free(char **array, const char *str, char c, int a);
void    ft_syntax(t_line *head);
char	**alloc(int l);
char	**ft_split(char *str, char c);
int    ft_cd(char *str);
t_line    *ft_put(char *line);
void    ft_ctr_c(int sig);
void    ft_red_args(t_line *head);
int     ft_syntax_pipe(char *str);
#endif