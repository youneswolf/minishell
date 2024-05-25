#include <stdio.h>
#include <string.h>
#include <Kernel/sys/syslimits.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "minishell.h"

int     ft_isalnum_str(char *str)
{
		int i = 0;
		while (str && str[i])
		{
      	if (isalpha(str[i]) || isdigit(str[i]))
        {
                return (1);
        }
		i++;
		}
        return (0);
}
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

char	*ft_strjoin(char *static_str, char *buff, int is_free)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len;

	if (!static_str && !buff)
		return (ft_strdup(""));
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
	if (is_free == 1)
		free(static_str);
	else if (is_free == 2)
	{
		(free(static_str), free(buff));
	}
	else if(is_free == 3)
		free(buff);
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
// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		++i;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

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

char	*ft_sub_str(char *s, unsigned int start, size_t len, int is_free)
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
	if (is_free == 1)
		free(s);
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
	while (s1 && s1[i])
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
		return (NULL);
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
		if (str[i] == '$' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}
int is_char(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}
void    ft_free_list3(t_line **str)
{
	t_line *to_be_free;
	t_line	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->str);
		free(prev);
	}
	// free(str);
	// t_line *next;

	// to_be_free = *str;
	// while (to_be_free)
	// {
	// 	if (to_be_free->next)
	// 		next = to_be_free->next;
	// 	free(to_be_free->str);
	// 	free(to_be_free);
	// 	to_be_free = next;
	// }
	// // free(to_be_free);
	// free(str);
}
void    ft_free_list2(t_line **str)
{
	t_line *to_be_free;
	t_line	*prev;
	to_be_free = *str;
	while (to_be_free)
	{
		prev = to_be_free;
		to_be_free = to_be_free->next;
		free(prev->str);
		free(prev);
	}
	// free(str);
	// t_line *next;

	// to_be_free = *str;
	// while (to_be_free)
	// {
	// 	if (to_be_free->next)
	// 		next = to_be_free->next;
	// 	free(to_be_free->str);
	// 	free(to_be_free);
	// 	to_be_free = next;
	// }
	// // free(to_be_free);
	// free(str);
}
t_line *get_exp_node(char *line_str)
{
	t_exp vars;
	vars.split = NULL;
	vars.i = 0;
	vars.j = 0;
		while (line_str && line_str[vars.i])
		{
			if (line_str[vars.i] == '$')
			{
				vars.str = ft_split(line_str, 32);
				while (vars.str[vars.j])
				{
					if (!vars.split)
						vars.split = ft_lst_new(ft_strdup(vars.str[vars.j]));
					else
					{
						vars.node = get_last_l(&vars.split);
						vars.node->next = ft_lst_new(ft_strdup(vars.str[vars.j]));
					}
					vars.j++;
				}
			ft_free_2d(vars.str);
			}
			vars.i++;
		}
	return (vars.split);
}
// int     ft_isalpha(int c)
// {
//         if (((unsigned char )c >= 65 && (unsigned char )c <= 90) 
//                 || ((unsigned char )c >= 97 && (unsigned char )c <= 122))
//         {
//                 return (1);
//         }
//         return (0);
// }

int check_for_first_elem(char *str)
{
	int i;

	i = 0;
	if (str && str[0] && str[0] == '$')
		return (0);
	while(str && str[i] && str[i] != '$')
	{
		if (str[i] != '.' || str[i] != ',' || str[i] != '/' || str[i] != '-' || str[i] != ':')
			return (1);		
		i++;
	}
	return (0);
}

int check_quotes(char *str)
{
	int i;
	char quote;
	int parity = 0;

	i = 0;
	if (str && str[0] && (str[0] == 39 || str[0] == 34))
	{
		quote = str[0];
		while (str[parity] == quote)
		{
			parity++;
		}
		i = parity;
		while (str[i])
			i++;
		i--;
		while (str[i] == quote)
		{
			i--;
			parity--;
		}
		if (parity == 0)
			return (quote);
	}
	return (0);
}

void expanding(t_exp *vars, int check , int quotes, t_env **env)
{
	while(vars->dollar_str[vars->i])
	{
		vars->j = 0;
		vars->dollar_str_space = ft_strtrim(vars->dollar_str[vars->i], " ", 1);
		if (vars->i == 0)
		{
			if (check == 0)
				vars->dollar_str_space = ft_strjoin("$",vars->dollar_str_space,3);
		}
		else
			vars->dollar_str_space = ft_strjoin("$",vars->dollar_str_space,3);
		if (vars->i == 0)
			vars->join = ft_strjoin(vars->join, expand(vars->dollar_str_space, env,1, quotes),2);
		else
			vars->join = ft_strjoin(vars->join, expand(vars->dollar_str_space, env,0, quotes),2);
		while (vars->dollar_str[vars->i] && vars->dollar_str[vars->i][vars->j]&&  vars->dollar_str[vars->i][vars->j] == ' ')
		{
			vars->join = ft_strjoin(vars->join, " ",1);
			vars->j++;
		}
		vars->i++;
		free(vars->dollar_str_space);
	}
}

void join_exp(t_exp *vars, t_env **env)
{
	vars->i = 0;
	int check ;
	int quotes = 42;
	int dollar;
	vars->dollar_str = ft_split(vars->split->str, '$');
	check  = check_for_first_elem(vars->split->str);
	quotes = check_quotes(vars->split->str);
	if (quotes == 39)
		quotes = 1;
	else if (quotes == 34)
		quotes = 2;
	expanding(vars, check, quotes, env);
	ft_free_2d(vars->dollar_str);

}

void join_exp_1dollar(t_exp *vars, t_env **env)
{
	vars->join = ft_strjoin(vars->join, expand(vars->split->str, env,1, 0),2);
	if (vars->split->next)
	{
		vars->join = ft_strjoin(vars->join," ",1);
	}
}

char *handle_expand(char *line_str, t_env **env)
{
	t_exp vars;
	vars.i = 0;
	vars.j = 0;
	vars.split = get_exp_node(line_str);
	free(line_str);
	vars.join = NULL;
	vars.str = NULL;
	vars.dollar_str = NULL;
	vars.node = vars.split;
	while (vars.split)
	{
		if (count_dollar(vars.split->str) > 1)
		{
			join_exp(&vars, env);
		}
		else 
		{
			join_exp_1dollar(&vars, env);
		}
		vars.split = vars.split->next;
	}
	ft_free_list2(&vars.node);
	if (!vars.join)
		return (ft_strdup(""));
	return (vars.join);
}
int is_number(char *str)
{
	if (str[1] && str[1] >= '0' && str[1] <= '9')
		return (1);
	return (0);
}
char *expand_nbr(char *str)
{
	char *expanded;

	expanded = ft_sub_str(str, 2, ft_strlen(str) -2, 0);
	if (!expanded)
		return ("");
	return (expanded);
}
void expand_vars(t_expan *vars)
{
	while (vars->sub && vars->sub[vars->i])
	{
		if (vars->sub[vars->i] == '.' || vars->sub[vars->i] == ',' || vars->sub[vars->i] == '/' || vars->sub[vars->i] == '-' || vars->sub[vars->i] == ':' || vars->sub[vars->i] == 34 || vars->sub[vars->i] == 39)
		{
			vars->j = vars->i;
			while (vars->sub [vars->j] && vars->sub[vars->j] != '$')
				vars->j++;
			vars->special = ft_sub_str(vars->sub, vars->i, vars->j - vars->i,0);
			vars->pre_var = ft_sub_str(vars->sub, 0, vars->i,0);
			break;
		}
		vars->i++;
	}
}
char *expand_env(t_expan *vars)
{
	while (vars->tmp && vars->var)
	{
		if (!ft_strncmp(vars->var, vars->tmp->env, ft_strlen(vars->var)))
		{
			vars->i = 0;
			free(vars->var);
			vars->var = ft_strjoin(vars->tmp->env,vars->special,3);
			while (vars->var && vars->var[vars->i] != '=')
				vars->i++;
			vars->var = ft_sub_str(vars->var, vars->i + 1, ft_strlen(vars->var) - vars->i - 1,1);
			vars->var = ft_strjoin(vars->pre_special,vars->var,2);
			return (vars->var);
		}
		vars->tmp = vars->tmp->next;
	}
	return (NULL);
}
void initialize_vars(t_expan *vars, t_env **env)
{
	vars->special = NULL;
	vars->pre_special = NULL;
	vars->sub = NULL;
	vars->pre_var = NULL;
	vars->tmp = *env;
	vars->i = 0;
	vars->j = 0;
}

char *expand(char *str, t_env **env, int last, int quotes)
{
	t_expan vars;
	initialize_vars(&vars, env);
	if (is_sgl_quote_ex(str,last) && is_char(str) && quotes != 2)
		return (ft_strdup(str));
	if (quotes == 1)
		return (ft_strdup(str));
	if (!if_dollar(str))
		return (ft_strdup(str));
	if (is_number(str))
		return (expand_nbr(str));
	while (str && str[vars.i] && str[vars.i] != '$')
		vars.i++;
	if (vars.i && vars.i != ft_strlen(str))
		vars.pre_special = ft_sub_str(str, 0, vars.i, 0);
	vars.sub = ft_sub_str(str, vars.i+1, (ft_strlen(str) - vars.i -1),0);
	vars.i = 0;
	expand_vars(&vars);
	if (vars.pre_var)
	{
		vars.var = ft_strjoin(vars.pre_var, "=",1);
		free(vars.sub);
	}
	else
		vars.var = ft_strjoin(vars.sub, "=",1);
	if (expand_env(&vars))
		return(vars.var);
	free(vars.var);
	return (ft_strjoin(vars.pre_special, vars.special,2));
}


void fill_null_env(t_env **mini_env)
{
	t_env *node;
	char *line;
	int len;
	int i;

	i = 0;
	char *first = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	node->env = first;
	node->printed = 0;
	node->next = NULL;
	*mini_env = node;
	fill_second_null_env(mini_env);
}

void fill_second_null_env(t_env **mini_env)
{
	char	buf[1024];
	char	*var = ft_strdup("PWD=");
	char *final;
	t_env *node;
	char *line;
	int i;
	i = 0;
	if (getcwd(buf, sizeof(buf)) == NULL)
        (perror("getcwd"), exit(EXIT_FAILURE));
	node = malloc(sizeof(t_env));
	if (!node)
		(ft_free_nodes(mini_env), exit(1));
	final = ft_strjoin(var, buf, 1);
	node->env = final;
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
int check_is_closed(char *str,int  sgl)
{
	int i;
	int j;
	int k;
	int count;

	count = 0;
	k = 0;
	j = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
		{
			j = 1;
			count++;
		}
		if (j && str[i] == '$' || sgl && str[i] == '$')
			k = 1;
		i++;
	}
	if (k && count %2 == 1)
		return (1);
	return (0);
}
int check_sgl_parity(char *str, int i, int sgl)
{
	int parity;
	sgl += count_sgl(str, i);
	parity = sgl / 2;
	// printf("aaa%d\n",sgl);
	// while (str && str[i] && str[i] == 39)
	// {
	// 	parity++;
	// 	i++;
	// }
	if (sgl %2 == 0 && sgl != 0 && parity % 2 == 1 && check_is_closed(str,sgl))
		return (1);
	// if (sgl %2 == 1)
		return (0);
	// printf("%d\n",parity);
	// printf("|%s|\n",str);
	// if (parity != 0 && parity % 2 == 0)
	// 	return (1);
	// return (0);
}
int count_sgl(char *str, int i)
{
	int count;
	if (str[i] && str[i] == 39)
		i = i+1;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	// printf("%d\n",count);
	return (count);
}
int is_sgl_quote_ex(char *str, int last)
{
	int i = 0;
	static int sgl;
	if (last == 1)
	{
		sgl = 0;
	}
	// if (last)
	// 	return(sgl=0, 1);
	// printf("%d\n",sgl);
	int past_sgl = sgl;
	int j = 0;
	int z = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
		{
			sgl++;
			j = 1;
		}
		if (str[i] == 39 && str[i + 1] && str[i + 1] == 34)
		{
			sgl += count_sgl(str, i);
			return (1);
		}
		if (str[i] == 34 && str[i + 1] && str[i + 1] == 39)
		{
			sgl += count_sgl(str, i);
			return (0);
		}
		// printf("%d|,%s\n",sgl,str);
		if (j && check_sgl_parity(str,i,sgl))
		{
			sgl += count_sgl(str, i);
			return (1);
		}
		// if (sgl != 0 &&sgl %2 == 0)

		// 	return(sgl= 0 ,1);
		if (str[i] == '$' && j)
		{
			sgl += count_sgl(str, i);
			return (1);
		}
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
	node->printed = 0;
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