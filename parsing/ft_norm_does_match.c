/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm_does_match.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:41:42 by ybellakr          #+#    #+#             */
/*   Updated: 2024/05/29 17:44:36 by ybellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_uttt(t_does_match *t, char *pat, char *text, int a)
{
	if (a == 0)
	{
		while (pat[t->i] == '*')
			t->i++;
	}
	else
	{
		while (text[t->j] && pat[t->i] && text[t->j] != pat[t->i])
			t->j++;
	}
}
