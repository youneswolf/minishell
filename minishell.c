/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/03/04 18:45:22 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_line	*ft_lstnew(char *str)
// {
// 	t_line	*new;

// 	new = (t_line *)malloc(sizeof(t_line));
//     new->str = strdup(str);
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	return (new);
// }

// void	add_list(t_line **lst, char *str)
// {
// 	t_line	*new;
// 	t_line	*temp;

// 	new = ft_lstnew(str);
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		new->next = NULL;
// 	}
// 	else
// 	{
// 		temp = *lst;
// 		while (temp->next != NULL)
// 		{
// 			temp = temp->next;
// 		}
// 		temp->next = new;
// 	}
// }


int is_there_exit(char *str)
{
    int i, j;

    i = 0;
    while (str[i])
    {
        if (str[i] == 'e' && str[i+1] == 'x' && str[i+2] == 'i' && str[i+3] == 't')
            return (1);
        i++;
    }
    return (0);
}

int ft_strcmp(char *str, char *str1)
{
    int i;

    i = 0;
    while (str[i] && str1[i])
    {
        if (str[i] != str1[i])
            return (0);
        i++;
    }
    return (1);
}

char    *ft_add_space_to_command(char *str)
{
    int i, count, j;
    char *new_line;

    i = 0;
    count = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '|' || str[i] == '>' || str[i] == '<'
        || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
             count++;
        i++;
    }
    new_line = malloc(i + 1 + count * 2);
    if (!new_line)
        return (perror("malloc"), NULL);
    i = 0;
    while (str[i])
    {
        if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
        {
            new_line[j] = ' ';
            new_line[j + 1] = str[i];
            new_line[j + 2] = str[i];
            new_line[j + 3] = ' ';
            j = j + 3;
            i++;
        }
        else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
        {
            new_line[j] = ' ';
            new_line[j + 1] = str[i];
            new_line[j + 2] = ' ';
            j = j + 2;
        }
        else
            new_line[j] = str[i];
        j++;
        i++;
    }
    new_line[j] = '\0';
    return (new_line);
}

void    ft_ctr(int sig)
{
    (void)sig;
    printf(RED"\nminishell$ "RESET);
    return ;
}

int main()
{
    struct sigaction sa;
    struct sigaction sa1;
    t_line *str;
    int     i = 0;
    char    *line;
    char    **holder;

    str = NULL;
    sa.sa_handler = ft_ctr_c;
    sa1.sa_handler = ft_ctr;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa1, NULL);
    while (1)
    {
        line = readline(RED"minishell$ "RESET);
        if (!SIGQUIT || line == NULL || is_there_exit(line))
        {
            if (line == NULL)
                (printf("exit!\n"), exit(0));
        }
        if (ft_strlen(line) > 0)
            add_history(line);
        line = ft_add_space_to_command(line);
        str = ft_put(line);
        ft_give_token(str);
        ft_syntax(str);
        while (str)
        {
            if (str->token == CMD)   
                printf(BLUE"[%s]"RESET, "CMD");
            else if (str->token == ARGS)
                printf(YELLOW"[%s]"RESET, "ARGS");
            else if (str->token == PIPE)
                printf(MAGENTA"[%s]"RESET, "PIPE");
            else if (str->token == IN_REDIR)
                printf(CYAN"[%s]"RESET, "IN_REDIR");
            else if (str->token == OUT_REDIR)
                printf(WHT"[%s]"RESET, "OUT_REDIR");
            else if (str->token == HERDOC)
                printf(GREEN"[%s]"RESET, "HERDOC");
            else if (str->token == OUT_FILE)
                printf(MAGENTA"[%s]"RESET, "OUT_FILE");
            else if (str->token == IN_FILE)
                printf(YELLOW"[%s]"RESET, "IN_FILE");
            else if (str->token == FILE)
                printf(YELLOW"[%s]"RESET, "FILE");
            else if (str->token == APPEND)
                printf(YELLOW"[%s]"RESET, "APPEND");
            else if (str->token == DELIMITER)
                printf(YELLOW"[%s]"RESET, "DELIMITER");
                printf("--%s--", str->str);
            str = str->next;
        }
        printf("\n");
        free(line);
    }
}