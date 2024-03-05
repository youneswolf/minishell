#include <stdio.h>
#include <string.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#define CMD "cmd"
#define PIPE "pipe"
#define ARGS "args"
#define IN_REDIR "in_redir"
#define OUT_REDIR "out_redir"
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
void fill_null_env(t_env **mini_env);
void fill_second_null_env(t_env **mini_env);
char *expand(t_line **line, t_env **env);
void	ft_free_nodes(t_env **a);
void exec_echo(t_line **line, t_env **env);
void fiLL_env(t_env **mini_env, char **env);
void exec_unset(t_env **mini_env, t_line **line);
void exec_env(t_env **mini_env, char *str);
void	env_list(t_env **mini_env, char *line);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char **cpy_in_2d(char **str);
char	*free2darray(char **array, int n);
int    ft_cd(char *str);
char	*ft_strdup(char *s1);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char *s1, char *set, int arg);
int     if_quote(char *str);
char	*skip_path(char *str);
char	*find_path(char **str);
char	*ft_strjoin(char *s1, char *s2);
char	*find_path(char **str);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int     ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
typedef struct line_s
{
    char *str;
    struct line_s *next;
}line_t;
