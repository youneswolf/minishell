/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:05:12 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:44 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include <sys/_types/_size_t.h>
# include <termios.h>
# include <Kernel/sys/syslimits.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <dirent.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <libc.h>

# define NONE -1
# define CMD 0
# define PIPE 1
# define ARGS 2
# define IN_REDIR 3
# define OUT_REDIR 4
# define HERDOC 5
# define OUT_FILE 6
# define IN_FILE 7
# define FILE 8
# define APPEND 10
# define DELIMITER 11
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
	int	j;
	int	does;
	int	is_out;
	int	index;
	int	k; 
	int	w;
	int	a;
	int	n;
	int	l;
	int	sss;
	int	www;
	int	zzz;
	int	z;
	int	zz;
	int	flag;
	int	mm;
	int	i;
	int	c;
}	t_long;

typedef struct s_does_match
{
	int	i;
	int	j;
	int	l;
	int	ll;
}	t_does_match;

typedef struct s_status1
{
	int	status;
	int	quote;
	int	index;
}	t_status1;

typedef struct s_remove
{
	int	count;
	int	flag;
	int	i;
}	t_remove;

typedef struct s_outfile
{
	char	**a;
	int		qq;
	int		ee;
}	t_outfile;

typedef struct s_put
{
	int	flag;
	int	i;
	int	j;
}	t_put;

typedef struct s_file
{
	int	i;
	int	z;
	int	q;
	int	b;
}	t_file;

typedef struct s_line
{
	char			*str;
	int				token;
	int				deja;
	int				quote;
	int				type_quote;
	int				flag;
	int				is_between_quote;
	t_status1		*status1;
	int				is_it_built_in;
	struct s_line	*next;
}	t_line;
typedef struct s_join
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;
}	t_join;
typedef struct s_status
{
	int		status;
	int		quote;
	int		index;
	t_line	*node;
}	t_status;

typedef struct s_start_end
{
	int	start;
	int	end;
}	t_stend;

typedef struct s_expand
{
	int		quote;
	char	*expa;
	char	*new_str;
	char	*s;
}	t_expand;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
	int				printed;
	int				deleted;
}	t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	char			*infile;
	int				in_or_out;
	char			*outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_holder
{
	int				here;
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
}	t_holder;
typedef struct s_last
{
	int		status;
	char	*line;
}	t_last;

typedef struct s_exp
{
	t_line	*split;
	t_line	*node;
	char	*dollar_str_space;
	char	*spaces;
	char	*join;
	char	**str;
	char	**dollar_str;
	char	*expand_var;
	int		j;
	int		i;
}	t_exp;

typedef struct s_expan
{
	t_env	*tmp;
	t_line	*line_tmp;
	char	*special;
	char	*pre_special;
	int		i;
	int		j;
	char	*var;
	char	*sub ;
	char	*pre_var;
}	t_expan;

typedef struct s_execution
{
	t_holder	*tmp;
	int			ppp;
	int			child_stat;
	int			pipe_fd[2];
	int			i;
	int			j;
	int			k;
	int			n;
	int			exit;
	int			wait_i;
	int			pid;
	int			origin_in;
	int			origin_out;
	t_holder	*doc_tmp;
}	t_execution;

typedef struct s_export
{
	char		*node_env;
	char		*var_name;
	char		*value;
	t_env		*tmp;
	t_env		*node;
	int			is_invalid;
	t_holder	*line_tmp;
	char		*join;
	int			j;
	int			i;
}	t_export;

typedef struct s_add_space
{
	int	i;
	int	count;
	int	flag;
}	t_add_space;

typedef struct s_unset
{
	t_env	*tmp;
	char	*value;
	t_line	*tmp1;
	int		i;
	int		ind;
}	t_unset;

void			ft_exit2(t_holder *str, int count);
void			ft_exit_utils(int k);
char			*expand_env(t_expan *vars);
void			ft_putchar_fd(char c, int fd);
int				check_quotes(char *str);
void			ft_putstr_fd(char *s, int fd);
int				ft_cmp(char *s, char *s1);
int				ft_is_numeric(char *str);
unsigned long	ft_atoi(char *str);
char			**ft_put_env_string(char **array, t_env *env);
void			ft_here_doc(char *lim, int pipe_fd[2], t_holder *atmp, \
				t_env **env);
void			check_which_built_in(t_execution *vars, t_env *env, \
				t_holder *holder);
char			*get_path(t_env *env, char *cmd);
void			here_doc_child(t_execution *vars, t_env *env);
void			exec_cmd(t_holder *holder, t_env *env, int pipe_fd[2]\
				, t_execution *vars);
void			exec_cmd_vars_init(t_execution *vars);
int				check_if_ctrl_c(t_execution *vars);
void			exec_dups_here(t_execution *vars);
void			here_piping(t_execution *vars);
void			ft_exit(t_holder *str, int count);
int				is_slash(char *str);
void			closing_files(t_execution *vars);
void			cmd_null_path(char *path, t_holder *holder);
void			ft_free_holder(t_holder **str);
void			cmd_file_stat(t_holder *holder, char **path);
int				ft_oppen_files(t_holder *node, t_last *status);
void			ft_f(int signum);
void			init_vars_cmd(t_execution *vars);
char			*skip_path(char *str);
char			*ft_strjoin_path(char *static_str, char *buff);
char			*ft_substr1(char *str, int start, int len, int not_);
void			ft_free_holder(t_holder **str);
int				ft_isalnum_str(char *str);
char			*ft_remove3(char *line);
char			*find_path(t_env *env);
char			*ft_remove_utils4(char *line, char *str, int j, int i);
int				ft_remove_utils3(char *str);
void			exec_env(t_env **mini_env);
void			exec_unset(t_env **mini_env, t_holder *holder);
void			exec_echo(t_holder *holder);
int				f_strcmp(char *str1, char *str2);
int				count_sgl(char *str, int i);
void			exec_export(t_holder **holder, t_env **env);
void			ft_handler_ctrt_herdoc(int signum);
int				f_strcmp(char *str1, char *str2);
int				ft_strcmp_asd(char *s1, char *s2);
char			*ft_itoa(int n);
char			*ft_remove_here(char *str);
int				execution_cmd(t_execution *vars, t_env *env, t_last *status);
void			cleaning_execution(t_execution *vars, t_holder **holder);
void			initial_vars(t_execution *vars, t_holder **holder);
int				here_doc_exec(t_execution *vars, t_env *env);
void			built_in_exec(t_execution *vars, t_env *env, t_holder *holder);
void			piping(t_execution *vars);
t_holder		*ft_create_holder_node(t_line *node, char *line);
int				ft_count_pipe(t_line *head);
char			*put_status_in_str(char *str, int status_int);
void			ft_execute_cmd(t_line *head);
int				ft_isalpha(int c);
char			*ft_sub_str(char *s, unsigned int start, \
				size_t len, int is_free);
char			*ft_strdup(char *s1);
char			*ft_strjoin(char *static_str, char *buff, int is_free);
size_t			ft_strlen(const char *s);
int				count(char *s, char c);
void			append_dollar_if_check(t_exp *vars, int check);
char			*word(char *str, char c);
int				ft_syntax(t_line *head, t_last	*status);
char			**alloc(int l);
char			**ft_split(char *str, char c);
int				ft_cd(char *str, t_env **mini_env);
int				count_dollar(char *str);
void			ft_put(char *str, t_line **head);
void			ft_red_args(t_line *head);
void			ft_expand_argument(t_env *env, t_line **linked_list);
char			*ft_handle_expand(char *line_str, char *arg);
void			ft_append_char(char **str, int c);
int				ft_surpass_chars(char *var);
char			*ft_arg_is_exist(t_env *env, char *var);
char			*ft_allocate_for_var(int flag, char *str, int i);
t_env			*ft_get_env(char **env);
static t_env	*ft_create_new_env(void);
int				ft_t_env_len(t_env *head);
static t_env	*ft_last_ft_node(t_env *top);
static t_env	*ft_new_node(char *value);
int				ft_push_value(char *value, t_env **head);
void			ft_free_env(t_env **head);
void			ft_remove_quote(t_line **str, char *line);
char			*ft_remove(t_line *tmp, char *line);
int				ft_strchr1(char *s, char c);
void			ft_checking_files(t_holder *node);
int				ft_count_2d(char **array);
int				ft_strcmp(char *s1, char *s2);
int				ft_cmp_built_in(char *str);
void			ft_handler_ctrl_c(int signum);
void			ft_free_2d(char **array);
void			put_env_value(t_export *vars, t_env **env);
void			check_validity(t_export *vars, t_env **env);
void			ft_print_export(t_env *head);
void			ft_putstr_export(char *s);
void			export_vars(t_export *vars, t_holder **holder, t_env **env);
void			ft_sort_list(t_env **env);
void			add_vars(t_export *vars, t_env **env);
void			declare_export(t_env *env);
void			if_not_in_env(t_export *vars, t_env **env);
void			ft_free_list(t_line **str, t_status *status);
void			redirect_append(int fd);
void			if_not_in_env1(t_export *vars, t_env **env);
void			redirect_output(int fd);
void			redirect_input(int fd);
t_line			*ft_lst_new(char *str);
int				if_dollar(char *str);
char			*handle_expand(char *line_str, t_env **env);
void			env_list(t_env **mini_env, char *line);
void			fill_env(t_env **mini_env, char **env);
t_env			*get_last(t_env **a);
void			ft_free_nodes(t_env **a);
void			fill_second_null_env(t_env **mini_env);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			fill_null_env(t_env **mini_env);
int				ft_isalnum(int c);
char			*expand(char *str, t_env **env, int last, int quotes);
char			*ft_substr(char *str, int start, int len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
static int		end_finder(char *s1, char *set);
char			*ft_strdup(char *s1);
static int		start_finder(char *s1, char *set);
char			*ft_strtrim(char *s1, char *set, int arg);
int				ft_count_pipe(t_line *head);
void			ft_pwd(t_env *mini_env);
int				is_sgl_quote(char *str);
int				is_sgl_quote_ex(char *str, int last);
void			ft_execute_cmd(t_line *head);
void			ft_give_token(t_line *head, t_status *status);
char			*ft_strdup(char *s1);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2, int is_free);
int				count(char *s, char c);
char			*word(char *str, char c);
char			**alloc(int l);
char			**ft_split(char *str, char c);
void			ft_red_args(t_line *head);
void			ft_expand_argument(t_env *env, t_line **linked_list);
void			ft_append_char(char **str, int c);
int				ft_surpass_chars(char *var);
char			*ft_arg_is_exist(t_env *env, char *var);
char			*ft_allocate_for_var(int flag, char *str, int i);
t_env			*ft_get_env(char **env);
static t_env	*ft_create_new_env(void);
int				ft_t_env_len(t_env *head);
static t_env	*ft_last_node(t_env *top);
static t_env	*ft_new_node(char *value);
int				ft_push_value(char *value, t_env **head);
void			ft_free_env(t_env **head);
void			ft_checking_files(t_holder *node);
char			*handle_expand_here(char *line_str, t_env **env);
t_line			*get_last_l(t_line **a);
char			*expand_here(char *str, t_env **env);
int				count_sgl_quote(char *str);
char			**ft_split1(const char *str, char c);
static char		**alloc1(int l);
void			ft_free_list2(t_line **str);
static int		ft_free(char **array, const char *str, char c, int a);
static char		*word1(const char *str, char c);
static int		count1(const char *s, char c);
char			**ft_does_it_matche(char *str);
int				ft_is_there(char *str);
int				ft_is_there_in_the_dir(char *pat, char *text);
int				ft_search_back(char *pattern, char *text, int l, int ll);
int				ft_str(char *str);
int				ft_status(int a, int status);
char			*handle_expand(char *line_str, t_env **env);
void			join_exp(t_exp *vars, t_env **env);
void			join_exp_1dollar(t_exp *vars, t_env **env, char *str);
void			initialize_vars(t_expan *vars, t_env **env);
t_line			*get_exp_node(char *line_str);
void			join_exp_here(t_exp *vars, t_env **env);
void			join_exp_1dollar_here(t_exp *vars, t_env **env);
int				check_for_first_elem(char *str);
void			ft_free_list3(t_line **str);
void			ft_heredoc(int signum);
char			*expand_nbr(char *str);
void			expand_vars(t_expan *vars);
int				is_char(char *str);
int				is_number(char *str);
int				check_sgl_parity(char *str, int i, int sgl);
void			ft_skip_empty_expand_utils(t_line *head, t_line *previous, \
				t_line *tmp);
void			ft_skip_empty_expand(t_line **node);
int				is_between_quotes(char *str);
int				ft_status(int a, int status);
int				int_len(int n);
int				ft_cmp_built_in(char *str);
void			ft_is_buil(t_line *str);
void			ft_set_token_to_none(t_line *str);
int				is_there_exit(char *str);
void			ft_add_space_utils(char *new_line, char *str, int quote, \
				t_add_space t);
char			*ft_add_space_to_command(char *str);
char			*ft_strnstr(const char *haystack, const char *needle, \
				size_t len);
void			execution(t_holder **holder, t_env *env, t_last *status);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
char			*ft_strchr(char *s, int c);
int				is_ambiguous(char *str);
void			ft_free_2d_am(char **array);
void			ft_null_tmp(t_holder **tmp);
void			ft_oppen_files_utiles1(t_holder *tmp, t_file *t);
int				ft_str(char *str);
int				ft_search_back(char *pattern, char *text, int l, int ll);
int				ft_is_there_in_the_dir(char *pattern, char *text);
int				ft_is_there(char *str);
int				ft_remove_utils3(char *str);
void			ft_lstnew_holder_utils(t_holder *new_);
int				ft_lstnew_holder_check(t_holder *new_);
t_holder		*ft_lstnew_holder(char *line);
t_holder		*last_node(t_holder *head);
t_holder		*add_list_holder(t_holder **lst, char *line);
int				ft_count_pipe(t_line *head);
int				ft_count_word(char *str);
int				ft_count_2d(char **a);
int				ft_create_holder_utils(t_holder *new_, t_line *tmp, \
				int *flag, int *j);
void			ft_create_holder_utils1(t_holder *new_, t_line *tmp, \
				int *j, int *flag);
int				ft_create_hoder_utils2(t_holder *new_, t_line *tmp, \
				int *flag, int *z);
void			ft_create_holder_utils3(t_line *tmp, t_holder *new_, int *z);
void			ft_create_holder_args(t_line *tmp, t_holder *new_, int *j);
void			ft_create_holder_args1(t_line *tmp, t_holder *new_, int *z);
int				ft_create_holder_outfile(t_line *tmp, t_holder *new_, \
				t_long *t);
int				ft_create_holder_infile(t_line *tmp, t_holder *new_, t_long *t);
int				ft_create_holder_append(t_line *tmp, t_holder *new_, t_long *t);
void			ft_ini(t_long *t);
int				ft_utils_norm_utils(t_line *tmp, t_holder *new_, t_long *t);
int				ft_utils_norm(t_line *tmp, t_holder *new_, t_long *t);
void			ft_exit2(t_holder *str, int count);

#endif