/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/14 17:37:35 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <string.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <fcntl.h>
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
typedef struct s_start_end
{
    int    start;
    int    end;
}        t_stend;

typedef struct s_expand
{
    int        quote;
    char    *expa;
    char    *new_str;
    char    *s;
}            t_expand;

typedef struct s_env
{
    char            *value;
    struct s_env    *next;
}                    t_env;

typedef struct s_cmd
{
    char    *cmd;
    char    **arg;
    char    *infile;
    int     in_or_out;
    char    *outfile;
    struct s_cmd *next;
}t_cmd;

typedef struct s_holder
{
    char    *cmd;
    char    **args;
    char    **file_in;
    char    **file_out;
    char    **append;
    int     *in;
    int     *out;
    int     *ap;
    struct s_holder *next;
}   t_holder;

t_holder    *ft_create_holder_node(t_line *node);
int     ft_count_pipe(t_line *head);
t_holder	*add_list_holder(t_holder **lst);
t_holder	*ft_lstnew_holder(void);
void    ft_pwd();
void    ft_execute_cmd(t_line *head);
void    ft_give_token(t_line *head);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int	count(char *s, char c);
char	*word(char *str, char c);
void    ft_syntax(t_line *head);
char	**alloc(int l);
char	**ft_split(char *str, char c);
int    ft_cd(char *str, t_env *mini_env);
t_line    *ft_put(char *line);
void    ft_red_args(t_line *head);
void	ft_expand_argument(t_env *env, t_line **linked_list);
char	*ft_handle_expand(t_env *env, char *arg);
void	ft_append_char(char **str, int c);
int	ft_surpass_chars(char *var);
char	*ft_arg_is_exist(t_env *env, char *var);
char	*ft_allocate_for_var(int flag, char *str, int i);
t_env    *ft_get_env(char **env);
static t_env    *ft_create_new_env(void);
int	ft_t_env_len(t_env *head);
static t_env	*ft_last_node(t_env *top);
static t_env	*ft_new_node(char *value);
int	ft_push_value(char *value, t_env **head);
void	ft_free_env(t_env **head);
void    ft_remove_quote(t_line **str);
char    *ft_remove(t_line *tmp);
void    ft_checking_files(t_holder *node);

//======================================================================
#endif