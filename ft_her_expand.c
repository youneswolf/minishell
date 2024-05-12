#include "minishell.h"

char	*ft_str_join(char *static_str, char *buff)
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
		return (NULL);
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
	return (str);
}
int	ft_isalpha(int c)
{
	if (((unsigned char )c >= 65 && (unsigned char )c <= 90)
		|| ((unsigned char )c >= 97 && (unsigned char )c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if ((char )c >= 48 && (char )c <= 57)
	{
		return (1);
	}
	return (0);
}
int     ft_isalnum(int c)
{
        if (ft_isalpha(c) || ft_isdigit(c))
        {
                return (1);
        }
        return (0);
}
int count_dollar(char *str)
{
	int i = 0;
	int count = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
int count_sgl_quote(char *str)
{
	int i = 0;
	int count = 0;
	while (str && str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}
char *handle_expand_here(char *line_str, t_env **env)
{
	t_exp vars;
	vars.i = 0;
	vars.j = 0;
	vars.split = get_exp_node(line_str);
	vars.join = NULL;
	vars.str = NULL;
	vars.dollar_str = NULL;
	vars.node = vars.split;
	while (vars.split)
	{
		if (count_dollar(vars.split->str) > 1)
		{
			join_exp_here(&vars, env);
		}
		else 
		{
			join_exp_1dollar_here(&vars, env);
		}
		vars.split = vars.split->next;
	}
	ft_free_list3(&vars.node);
	if (!vars.join)
		return ("");
	return (vars.join);
}
void join_exp_here(t_exp *vars, t_env **env)
{
	vars->i = 0;
	int check ;
	vars->dollar_str = ft_split(vars->split->str, '$');
	check  = check_for_first_elem(vars->dollar_str[0]);
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
		vars->join = ft_strjoin(vars->join, expand_here(vars->dollar_str_space, env),2);
		while (vars->dollar_str[vars->i] &&vars->dollar_str[vars->i][vars->j]&&  vars->dollar_str[vars->i][vars->j] == ' ')
		{
			vars->join = ft_strjoin(vars->join, " ",1);
			vars->j++;
		}
		vars->i++;
		free(vars->dollar_str_space);
	}
		ft_free_2d(vars->dollar_str);
}
void join_exp_1dollar_here(t_exp *vars, t_env **env)
{
	vars->join = ft_strjoin(vars->join, expand_here(vars->split->str, env),2);
	if (vars->split->next)
	{
		vars->join = ft_strjoin(vars->join," ",1);
	}
}
char *expand_here(char *str, t_env **env)
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
	i = 0;
	int j = 0;
		while (str && str[i] != '$')
			i++;
		if (i && i != ft_strlen(str))
		{
			pre_special = ft_substr(str, 0, i);
		}
		sub = ft_sub_str(str, i+1, (ft_strlen(str) - i -1),0);
	i = 0;
	while (sub && sub[i])
	{
		if (sub[i] == '.' || sub[i] == ',' || sub[i] == '/' || sub[i] == '-' || sub[i] == ':' || sub[i] == '_' || sub[i] == 34 || sub[i] == 39)
		{
			j = i;
			while (sub [j] && sub[j] != '$')
				j++;
			special = ft_sub_str(sub, i, j - i,0);
			pre_var = ft_sub_str(sub, 0, i,0);
			break;
		}
		i++;
	}
	if (pre_var)
	{
		var = ft_strjoin(pre_var, "=",1);
		free(sub);
	}
	else
		var = ft_strjoin(sub, "=",1);
	while ((tmp && pre_var) || (tmp && var))
	{
		if (!ft_strncmp(var, tmp->env, ft_strlen(var)))
		{
			i = 0;
			free(var);
			var = ft_strjoin(tmp->env,special,0);
			while (var && var[i] != '=')
				i++;
			var = ft_sub_str(var, i + 1, ft_strlen(var) - i - 1,1);
			var = ft_strjoin(pre_special,var,3);
			return (var);
		}
		tmp = tmp->next;
	}
	free(var);
	i = 0;
	j = 42;
	// if (if_dollar(str))
	// {
	// 	while (str[i] && str[i] != '$')
	// 	{
	// 		i++;
	// 	}
	// 	while (str[i])
	// 	{
	// 		if (ft_isalnum(str[i]) == 1)
	// 		{
	// 			return (pre_special);
	// 		}
	// 		else
	// 			return (str);
	// 	}
	// 	return ("");
	// }
	// if (str && str[0] == '$')
	// {
	// 	pre_var = ft_strjoin(pre_special, special,2);
	// 	return (ft_strjoin("$", pre_var,3));
	// }
	return (ft_strjoin(pre_special, special,2));
}