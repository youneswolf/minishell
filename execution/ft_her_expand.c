/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:40:59 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/26 14:06:03 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free(line_str);
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
void isolate_specials_and_var(t_expan *vars)
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
char *expand_here(char *str, t_env **env)
{
	t_expan vars;
	initialize_vars(&vars, env);
		while (str && str[vars.i] != '$')
			vars.i++;
		if (vars.i && vars.i != ft_strlen(str))
		{
			vars.pre_special = ft_substr(str, 0, vars.i);
		}
		vars.sub = ft_sub_str(str, vars.i+1, (ft_strlen(str) - vars.i -1),0);
	vars.i = 0;
	isolate_specials_and_var(&vars);
	if (vars.pre_var)
	{
		vars.var = ft_strjoin(vars.pre_var, "=",1);
		free(vars.sub);
	}
	else
		vars.var = ft_strjoin(vars.sub, "=",1);
	if(expand_env(&vars))
		return(vars.var);
	free(vars.var);
	vars.i = 0;
	vars.j = 42;
	return (ft_strjoin(vars.pre_special, vars.special,2));
}