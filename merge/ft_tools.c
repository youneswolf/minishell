#include <stdio.h>
#include <string.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "minishell.h"

t_env	*get_last(t_env **a)
{
	t_env	*tmp;
	if (!(*a)->next)
		return (*a);
	tmp = *a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_free1(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

// t_line	*get_last_l(t_line **a)
// {
// 	t_line	*tmp;

// 	tmp = *a;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	return (tmp);
// }

t_line	*get_last_l(t_line **a)
{
	t_line	*tmp;
	if (!(*a)->next)
		return (*a);
	tmp = *a;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_strjoin(char *static_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!static_str && !buff)
		return (NULL);
	if (!static_str && buff)
		return (ft_strdup(buff));
	if (!buff && static_str)
		return (ft_strdup(static_str));
	len = ft_strlen(static_str);
	str = malloc(sizeof(char) * (len + ft_strlen(buff)) + 1);
	if (!str)
		return (ft_free1(&static_str));
	i = 0;
	j = 0;
	while (static_str && static_str[i] != '\0')
	{
		str[i] = static_str[i];
		i++;
	}
	while (buff && buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	// free(static_str);
	return (str);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;
// 	int		res;

// 	res = 0;
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (s1[i] == '\0' && s2[i] == '\0')
// 		{
// 			return (0);
// 		}
// 		if ((s1 && s2 ) && (unsigned char)s1[i] != (unsigned char)s2[i])
// 		{
// 			res = (unsigned char)s1[i] - (unsigned char)s2[i];
// 			return (res);
// 		}
// 		i++;
// 	}
// 	return (res);
// }
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	char	x;
	int		i;

	i = 0;
	x = (char)c;
	while (s[i])
	{
		if (s[i] == x)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == x)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	len = 0;
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[len])
	{
		len++;
	}
	return (len);
}
// size_t	ft_strlen(const char *str)
// {
// 	if (!str)
// 		return (0);
// 	size_t	i;
// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		return (ft_strdup(""));
	if (i - start < len)
		len = i - start;
	dst = (char *)malloc(sizeof(char) * (len) + 1);
	if (!dst)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dst[i] = s[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) *(i + 1));
	if (!dest)
	{
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	int	start_finder(char *s1, char *set)
{
	size_t	i;
	size_t	len;

	if (!set)
		return (ft_strlen(s1) - 1);
	if (s1[0] == '\0')
	{
		return (0);
	}
	len = ft_strlen(s1);
	i = 0;
	while (i < len && ft_strchr(set, s1[i]))
	{
		i++;
	}
	return (i);
}

static	int	end_finder(char *s1, char *set)
{
	size_t	i;
	size_t	len;

	if (!set)
		return (0);
	if (s1[0] == '\0')
	{
		return (0);
	}
	len = ft_strlen(s1) - 1;
	i = start_finder(s1, set);
	while (len > i && ft_strchr(set, s1[len]))
	{
		len--;
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set, int arg)
{
	size_t	start;
	size_t	end;
	size_t	res_len;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = start_finder(s1, set);
	end = end_finder(s1, set);
	res_len = end - start + 1;
	result = (char *)malloc(((res_len + 1)) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, res_len + 1);
	result[res_len] = '\0';
	if (arg == 0)
		free(s1);
	return (result);
}
t_line *ft_lst_new(char *str)
{
	t_line *line;
	
	line = malloc(sizeof(t_line));
	if (!line)
		exit(0);
	line->str = str;
	line->next = NULL;
	return (line);
}
int	if_dollar(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
char *handle_expand(t_line **line, t_env **env)
{
	t_line *line_tmp = *line;
	t_line *split = NULL;
	t_line *node;
	char *join = NULL;
	char **str = NULL;
	char **dollar_str;
	int i = 0;
	int j = 0;
	printf("%s\n",line_tmp->str);
	while (line_tmp)
	{
		while (line_tmp && line_tmp->str && line_tmp->str[i])
		{
			if (line_tmp->str[i] == '$')
			{
				str = ft_split(line_tmp->str, 42);
				// printf("%s\n",line_tmp->str);
				while (str[j])
				{
					if (!split)
						split = ft_lst_new(str[j]);
					else
					{
						node = get_last_l(&split);
						node->next = ft_lst_new(str[j]);
					}
					j++;
				}
			}
			i++;
		}
		line_tmp = line_tmp->next;
	}
	while (split)
	{
		join = ft_strjoin(join, expand(&split, env));
		if (split->next)
			join = ft_strjoin(join," ");
		split = split->next;
	}

	if (!join)
		return ("");
	return (join);
}
char *expand(t_line **line, t_env **env)
{
	t_env *tmp;
	t_line *line_tmp;
	char *special = NULL;
	char *pre_special = NULL;
	int i;
	char *var;
	char *sub;
	char *pre_var = NULL;
	tmp = *env;
	line_tmp = *line;
	i = 0;
	int j = 0;
	if ( line_tmp && (line_tmp->str[0] == 34 || line_tmp->str[ft_strlen(line_tmp->str) - 1] == 34))
	{
		sub = ft_strtrim(line_tmp->str, "\"", 1);
		while (sub && sub[i] != '$')
			i++;
		if (i && i != ft_strlen(line_tmp->str))
		{
			pre_special = ft_substr(sub, 0, i);
		}
		if (line_tmp && line_tmp->str[0] == 34)
			sub = ft_substr(line_tmp->str, i+2, (ft_strlen(line_tmp->str) - i - 1));
		else 
			sub = ft_substr(line_tmp->str, i+1, (ft_strlen(line_tmp->str) - i - 1));
		sub = ft_strtrim(sub, "\"", 1);
	}
	else
	{
		while (line_tmp && line_tmp->str[i] != '$')
			i++;
		if (i && i != ft_strlen(line_tmp->str))
		{
			pre_special = ft_substr(line_tmp->str, 0, i);
		}
		sub = ft_substr(line_tmp->str, i+1, (ft_strlen(line_tmp->str) - i -1));
	}
	i = 0;
	while (sub && sub[i])
	{
		if (sub[i] == '.' || sub[i] == ',' || sub[i] == '/' || sub[i] == '-' || sub[i] == ':' || sub[i] == '_')
		{
			j = i;
			while (sub [j] && sub[j] != '$')
				j++;
			special = ft_substr(sub, i, j - i);
			pre_var = ft_substr(sub, 0, i);
			break;
		}
		i++;
	}
	if (pre_var)
		var = ft_strjoin(pre_var, "=");
	else
		var = ft_strjoin(sub, "=");
	// printf("%s\n",var);
	while ((tmp && pre_var) || (tmp && var))
	{
		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
		{
			i = 0;
			var = ft_strjoin(tmp->env,special);
			while (var && var[i] != '=')
				i++;
			var = ft_substr(var, i + 1, ft_strlen(var) - i - 1);
			var = ft_strjoin(pre_special,var);
			return (var);
		}
		tmp = tmp->next;
	}
	if (!if_dollar(line_tmp->str))
	{
		pre_var = ft_strtrim(line_tmp->str, "\"", 1);
		pre_var = ft_strtrim(pre_var, "\'", 1);
		return (pre_var);
	}
	return (pre_special);
}


void fill_null_env(t_env **mini_env)
{
	t_env *node;
	char *line;
	int len;
	int i;

	i = 0;
	char first[1024] = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	line = malloc(sizeof(char) * ft_strlen(first) + 1);
	if (!line)
		exit(1);
	while (first[i])
	{
		line[i] = first[i];
		i++;
	}
	line[i] = '\0';
	node->env = line;
	node->next = NULL;
	*mini_env = node;
	fill_second_null_env(mini_env);
}

void fill_second_null_env(t_env **mini_env)
{
	char	buf[1024];
	char	var[5] = "PWD=";
	t_env *node;
	char *line;
	int i;

	i = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
        (perror("getcwd"), exit(EXIT_FAILURE));
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	line = malloc(sizeof(char) * ft_strlen(buf) + 5);
	if (!line)
		exit(0);
	while (var[i])
	{
		line[i] = var[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		line[i + 4] = buf[i];
		i++;
	}
	line[i+4] = '\0';
	node->env = line;
	node->next = NULL;
	(*mini_env)->next = node;
}

void	ft_free_nodes(t_env **a)
{
	t_env	*head;
	t_env	*tobefreed;

	head = *a;
	while (head != NULL)
	{
		tobefreed = head;
		head = head->next;
		free(tobefreed);
	}
	*a = NULL;
}

void fiLL_env(t_env **mini_env, char **env)
{
	char *line;
	int	i;
	int j;

	i = 0;
	while (env[i])
	{
		j = 0;
		line = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!line)
			exit(0);
		while (env[i][j])
		{
			line[j] = env[i][j];
			j++;
		}
		line[j] = '\0';
		env_list(mini_env, line);
		i++;

	}
}
int is_sgl_quote(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
void	env_list(t_env **mini_env, char *line)
{
	t_env	*node;
	t_env	*last_node;

	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	node->env = line;
	node->next = NULL;
	if (!(*mini_env))
	{
		*mini_env = node;
	}
	else
	{
		last_node = get_last(mini_env);
		last_node->next = node;
	}
}