/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/04/02 20:27:37 by asedoun          ###   ########.fr       */
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
#include <readline/history.h>
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
    int status;
    int is_it_built_in;
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
    char            *env;
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
    char    **her_doc;
    int     *in;
    int     *out;
    int     *ap;
    struct s_holder *next;
}   t_holder;
t_holder        *ft_create_holder_node(t_line *node);
int             ft_count_pipe(t_line *head);
// t_holder        *add_list_holder(t_holder **lst, char *line);
// t_holder	    *ft_lstnew_holder(char *line);
void            ft_pwd();
void            ft_execute_cmd(t_line *head);
void            ft_give_token(t_line *head);
char	        *ft_strdup(char *s1);
char	        *ft_strjoin(char *s1, char *s2);
size_t	        ft_strlen(const char *s);
char	        *ft_strjoin(char *s1, char *s2);
int	            count(char *s, char c);
char	        *word(char *str, char c);
int             ft_syntax(t_line *head);
char	        **alloc(int l);
char	        **ft_split(char *str, char c);
int             ft_cd(char *str, t_env *mini_env);
void            ft_put(char *str, t_line **head);
void            ft_red_args(t_line *head);
void	        ft_expand_argument(t_env *env, t_line **linked_list);
char	        *ft_handle_expand(t_env *env, char *arg);
void	        ft_append_char(char **str, int c);
int             ft_surpass_chars(char *var);
char	        *ft_arg_is_exist(t_env *env, char *var);
char	        *ft_allocate_for_var(int flag, char *str, int i);
t_env           *ft_get_env(char **env);
static t_env    *ft_create_new_env(void);
int	            ft_t_env_len(t_env *head);
static t_env	*ft_last_node(t_env *top);
static t_env	*ft_new_node(char *value);
int	            ft_push_value(char *value, t_env **head);
void            ft_free_env(t_env **head);
void            ft_remove_quote(t_line **str, char *line);
char            *ft_remove(t_line *tmp, char *line);
void            ft_checking_files(t_holder *node);
int             f_strcmp(char *str1, char *str2);
int		        ft_cmp_built_in(char *str);
void            ft_handler_ctrl_c(int signum);
void	        ft_free_2d(char **array);
void            ft_free_list(t_line **str);
void    redirect_append(int fd);
void    redirect_output(int fd);
void    redirect_input(int fd);
t_line *ft_lst_new(char *str);
int	if_dollar(char *str);
char *handle_expand(t_line **line, t_env **env);
void	env_list(t_env **mini_env, char *line);
void fiLL_env(t_env **mini_env, char **env);
t_env	*get_last(t_env **a);
void	ft_free_nodes(t_env **a);
// char *expand(t_line **line, t_env **env);
void fill_second_null_env(t_env **mini_env);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void fill_null_env(t_env **mini_env);
char *expand(t_line **str, t_env **env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
static	int	end_finder(char *s1, char *set);
char	*ft_strdup(char *s1);
static	int	start_finder(char *s1, char *set);
char	*ft_strtrim(char *s1, char *set, int arg);
// t_holder    *ft_create_holder_node(t_line *node);
int     ft_count_pipe(t_line *head);
// t_holder	*add_list_holder(t_holder **lst);
// t_holder	*ft_lstnew_holder(void);
void    ft_pwd();
int is_sgl_quote(char *str);
void    ft_execute_cmd(t_line *head);
void    ft_give_token(t_line *head);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
int	count(char *s, char c);
char	*word(char *str, char c);
// void    ft_syntax(t_line *head);
char	**alloc(int l);
char	**ft_split(char *str, char c);
int    ft_cd(char *str, t_env *mini_env);
// t_line    *ft_put(char *line);
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
// void    ft_remove_quote(t_line **str);
// char    *ft_remove(t_line *tmp);
void    ft_checking_files(t_holder *node);

//======================================================================
#endif