/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/01 15:38:32 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <dirent.h>
#include <readline/history.h>
#include <libc.h>

// FILE	*gfp;

// static void	*__malloc(size_t size, int line, const char *file)
// {
// 	void	*ptr;

// 	ptr = malloc(size);
// 	fprintf(gfp, "dct[%p] = ['malloc', '%p', %i, '%s']\n",
// 		ptr, ptr, line, file);
// 	fflush(gfp);
// 	return (ptr);
// }

// static void	__free(void *ptr, int line, const char *file)
// {
// 	fprintf(gfp, "dct[%p] = ['free', '%p', %i, '%s']\n",
// 		ptr, ptr, line, file);
// 	fflush(gfp);
// 	free(ptr);
// }
// /**/
// # define malloc(x) __malloc(x, __LINE__, __FILE__)
// # define free(x) __free(x, __LINE__, __FILE__)

#define NONE -1
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

typedef struct s_long
{
	int j; 
	int	k; 
	int	w;
	int a;
	int n;
	int l;
	int	sss;
	int	www;
	int	zzz;
	int z;
	int zz;
	int flag;
	int	mm;
	int	i;
	int	c;
}	t_long;

typedef struct s_line
{
    char            *str;
    int             token;
	int				deja;
    int             quote;
    int             type_quote;
    int             flag;
	int 			is_between_quote;
    int             is_it_built_in;
    struct s_line   *next;
}                   t_line;

typedef struct s_status
{
    int     status;
    int     quote;
    char    *lastdir;
	int		index;
	t_line	*node;
}           t_status;

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
	int				printed;
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

// typedef struct s_herdoc
// {

// } t_herdoc;
typedef struct s_holder
{
	char			*cmd;
	char			**args;
	char			**file_in;
	int				*infile_index;
	char			**file_out;
	int				*outfile_index;
	char			**append;
	int				*append_index;
	char			**her_doc;
	int				*in;
	int				*out;
	int				*ap;
	char			**args_built_in;
	char			*cmd_built_in;
	int				nbr_file;
	struct s_holder	*next;
}   				t_holder;


extern	struct termios    attr;

// echo $USER << 1 cat
// echo "''''""$USER.$"'"$$USER"'"'"
// echo "$"
int				ft_oppen_files(t_holder *node);
void    		ft_f(int signum);
char			*ft_substr1(char *str, int start, int len, int not_);
void			ft_free_holder(t_holder **str);
int				ft_isalnum_str(char *str);
char    		*ft_remove3(char *line);
char			*ft_remove_utils4(char *line, char *str, int j, int i);
int				ft_remove_utils3(char *str);
void 			exec_env(t_env **mini_env );
void 			exec_unset(t_env **mini_env, t_holder *holder);
void 			exec_echo(t_holder *holder);
int 			f_strcmp(char *str1, char *str2);
void 			exec_export(t_holder **holder, t_env **env);
void    		ft_handler_ctrt_herdoc(int signum);
int 			f_strcmp(char *str1, char *str2);
int				ft_strcmp_asd(char *s1,  char *s2);
char    		*ft_remove_here(char *str);
t_holder    	*ft_create_holder_node(t_line *node, char *line);
int         	ft_count_pipe(t_line *head);
// t_holder        *add_list_holder(t_holder **lst, char *line);
// t_holder	    *ft_lstnew_holder(char *line);
void       		ft_pwd();
void        	ft_execute_cmd(t_line *head);
int				ft_isalpha(int c);
char			*ft_sub_str(char *s, unsigned int start, size_t len, int is_free);
// void        	ft_give_token(t_line *head);
char	    	*ft_strdup(char *s1);
char			*ft_strjoin(char *static_str, char *buff, int is_free);
// char	        *ft_strjoin(char *s1, char *s2);
size_t	    	ft_strlen(const char *s);
// char	        *ft_strjoin(char *s1, char *s2);
int	        	count(char *s, char c);
char	        *word(char *str, char c);
int				ft_syntax(t_line *head, t_status *status);
char	        **alloc(int l);
char	        **ft_split(char *str, char c);
int             ft_cd(char *str, t_env *mini_env, t_line *head);
int				count_dollar(char *str);
void            ft_put(char *str, t_line **head);
void            ft_red_args(t_line *head);
void	        ft_expand_argument(t_env *env, t_line **linked_list);
char	        *ft_handle_expand(char *line_str, char *arg);
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
int				ft_strchr1(char *s, char c);
void            ft_checking_files(t_holder *node);
int				ft_count_2d(char **array);
int				ft_strcmp(char *s1,  char *s2);
int		        ft_cmp_built_in(char *str);
void            ft_handler_ctrl_c(int signum);
void	        ft_free_2d(char **array);
void            ft_free_list(t_line **str, t_status *status);
void    		redirect_append(int fd);
void    		redirect_output(int fd);
void    		redirect_input(int fd);
t_line 			*ft_lst_new(char *str);
int				if_dollar(char *str);
char			*handle_expand(char *line_str, t_env **env);
void			env_list(t_env **mini_env, char *line);
void			fiLL_env(t_env **mini_env, char **env);
t_env			*get_last(t_env **a);
void			ft_free_nodes(t_env **a);
// char *expand(t_line **line, t_env **env);
void 			fill_second_null_env(t_env **mini_env);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void 			fill_null_env(t_env **mini_env);
int   			ft_isalnum(int c);
char 			*expand(char *str, t_env **env);
char 			*ft_substr(char *str, int start, int len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
static			int	end_finder(char *s1, char *set);
char			*ft_strdup(char *s1);
static			int	start_finder(char *s1, char *set);
char			*ft_strtrim(char *s1, char *set, int arg);
// t_holder    *ft_create_holder_node(t_line *node);
int     		ft_count_pipe(t_line *head);
// t_holder	*add_list_holder(t_holder **lst);
// t_holder	*ft_lstnew_holder(void);
void    		ft_pwd();
int 			is_sgl_quote(char *str);
void    		ft_execute_cmd(t_line *head);
void			ft_give_token(t_line *head, t_status *status);
char			*ft_strdup(char *s1);
// char	*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2, int is_free);
int				count(char *s, char c);
char			*word(char *str, char c);
// void    ft_syntax(t_line *head);
char			**alloc(int l);
char			**ft_split(char *str, char c);
// int    ft_cd(char *str, t_env *mini_env);
// t_line    *ft_put(char *line);
void    		ft_red_args(t_line *head);
void			ft_expand_argument(t_env *env, t_line **linked_list);
// char	*ft_handle_expand(char *line_str, char *arg);
void			ft_append_char(char **str, int c);
int				ft_surpass_chars(char *var);
char			*ft_arg_is_exist(t_env *env, char *var);
char			*ft_allocate_for_var(int flag, char *str, int i);
t_env   		*ft_get_env(char **env);
static t_env    *ft_create_new_env(void);
int				ft_t_env_len(t_env *head);
static t_env	*ft_last_node(t_env *top);
static t_env	*ft_new_node(char *value);
int				ft_push_value(char *value, t_env **head);
void			ft_free_env(t_env **head);
// void    ft_remove_quote(t_line **str);
// char    *ft_remove(t_line *tmp);
void    		ft_checking_files(t_holder *node);
char 			*handle_expand_here(char *line_str, t_env **env);
t_line			*get_last_l(t_line **a);
char 			*expand_here(char *str, t_env **env);
int 			count_sgl_quote(char *str);
char			**ft_split1(const char *str, char c);
static char		**alloc1(int l);
void    ft_free_list2(t_line **str);
static int		ft_free(char **array, const char *str, char c, int a);
static char		*word1(const char *str, char c);
static int		count1(const char *s, char c);
char 			**ft_does_it_matche(char *str);
int 			ft_is_there(char *str);
int 			ft_is_there_in_the_dir(char *pattern, char *text);
int    			ft_search_back(char *pattern, char *text, int l, int ll);
int 			ft_str(char *str);
//======================================================================
#endif