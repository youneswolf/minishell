/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asedoun <asedoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:36:46 by asedoun           #+#    #+#             */
/*   Updated: 2024/03/28 23:02:18 by asedoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_str_len(char *s);
char	*ft_free(char **str);
char	*ft_str_join(char *left_str, char *buff);
char	*skip_nl(char *left_str);
char	*ft_str_chr(char *s, int c);
char	*get_next_line(int fd);
#endif
