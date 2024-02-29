/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:51:57 by ybellakr          #+#    #+#             */
/*   Updated: 2024/02/29 15:54:56 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	add_list(line_t **lst, int val)
// {
// 	line_t	*new;
// 	line_t	*temp;

// 	new = ft_lstnew(val);
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

// line_t	*ft_lstnew(int content)
// {
// 	line_t	*new;

// 	new = (line_t *)malloc(sizeof(line_t));
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	return (new);
// }
void    ft_ctr_d(int sig)
{
    (void)sig;
    printf("test\n");
    exit(1);
}

int main()
{

    char *str;
    struct sigaction ctr_d;

    ctr_d.sa_handler = ft_ctr_d;
    if (sigaction(SIGTERM, &ctr_d, NULL) == -1)
        return (printf("failed in sigaction"), 0);
    while (1)
    {
        str = readline("minishell$ ");
        printf("==={%s}===\n", str);
    }
}