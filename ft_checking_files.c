// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_checking_files.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/14 17:06:44 by ybellakr          #+#    #+#             */
// /*   Updated: 2024/04/28 12:04:59 by ybellakr         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


#include "minishell.h"

// int is_ambiguous(char *str)
// {
//     int i = 0;
//     int j = 0;
//     if (str && str[0] == 32)
//     {
//         while(str[i] && str[i] == 32)
//             i++;
//         if (!str[i])
//             return (1);
//     }
//     i = 0;
//     while (str && str[i])
//     {
//         if (str[i] == ' ')
//             j = 1;
//         if (j == 1 && ft_isalnum(str[i]))
//             return (1);
//         i++;
//     }  
//     return (0);
// }

// int    ft_oppen_files(t_holder *node)
// {
//     t_holder    *tmp;
//     int         i;
//     int         z;
//     int         q;
//     int         b;

//     tmp = node;
//     i = 0;
//     z = 0;
//     q = 0;
//     b = 0;
//     while (tmp && (i < tmp->nbr_file))
//     {
//         if (tmp->outfile_index[b] == i)
//         {
//         if(!is_ambiguous(tmp->file_out[b]))
//         {
//             tmp->out[b] = open(tmp->file_out[b], O_CREAT| O_RDWR, 0644);
//             if (tmp->out[b] == -1)
//             {
//                 write(2, "such file or directory\n", 26);
//                     return (0);
//             }
//             b++;
//         }
//         else
//         {
//             printf("bash: %s: ambiguous redirect\n", tmp->file_out[b]);
//             tmp->out[b] = -7;
//         }
//         }
//         else if (tmp->infile_index[z] == i)
//         {
//             tmp->in[z] = open(tmp->file_in[z], O_RDONLY);
//             if(!is_ambiguous(tmp->file_in[i]))
//             {
//             if (tmp->in[z] == -1)
//             {
//                 write(2, "such file or directory\n", 24);
//                 return (0);
//             }
//             z++;
//             }
//             else
//             {
//                 printf("bash: %s: ambiguous redirect\n", tmp->file_in[z]);
//                  tmp->in[z] = -7;

//             }
//         }
//         else if (tmp->append_index[q] == i)
//         {
//             if(!is_ambiguous(tmp->append[q]))
//             {
//             tmp->ap[q] = open(tmp->append[q], O_CREAT| O_RDWR | O_APPEND, 0644);
//             if (tmp->ap[q] == -1)
//             {
//                 write(2, "such file or directory\n", 26);
//                 return (0);
//             }
//             q++;
//             }
//             else
//             {
//                  printf("bash: %s: ambiguous redirect\n", tmp->append[q]);
//                 tmp->ap[q] = -7;
                
//             }
//         }  
//         i++;
//     }
//     return (1);
// }

// void    ft_checking_files(t_holder *node)
// {
//     t_holder    *tmp;
//     int         i, j, k, check, b, n, z;


//     tmp = node;
//     i = 0;
//     j = 0;
//     b = 0;
//     k = 0;
//     n = 0;
//     z = 0;
//     while (tmp)
//     {
//         check  = 0;
//         while (tmp->file_in[b])
//         {
//             // if (tmp->file_in[i])
//             // {
//                 if(!is_ambiguous(tmp->file_in[i]))
//                 {
//                 tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
//                 if (tmp->in[i] == -1)
//                 {
//                     // ft_putstr_fd(2, in[i]);
//                     write(2, "such file or directory\n", 24);
//                     check  = -42;
//                     // return ;
//                 }
//                 i++;
                
//             }
//             // else
//             // {
//             //             tmp->cmd = NULL;
//             //         tmp->args[0] = NULL;
//             //         write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//             // }
//             b++;
//         }
//         // printf("-------%s-----\n",tmp->file_out[0]);
//         while (tmp->file_out[n])
//         {
//             if (tmp->file_out[j])
//             {
//                 // if (!is_ambiguous(tmp->file_out[j]))
//                 // {
//                 if (check != -42)
//                 {
//                     tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
//                     if (tmp->out[j] == -1)
//                     {
//                         write(2, "such file or directory\n", 26);
//                         // return ;
//                     }
//                     j++;
//                 }
//                 // }
//                 // else
//                 // {
//                 //     tmp->cmd = NULL;
//                 //     tmp->args[0] = NULL;
//                 //     write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//                 // }
//             }
//             n++;
//         }
//         while (tmp->append[z])
//         {
//             if (tmp->append[k])
//             {
//                 if (!is_ambiguous(tmp->append[k]))
//                 {
//                 tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
//                 if (tmp->ap[k] == -1)
//                     write(2, "such file or directory\n", 26);
//                 k++;
//                 }
//                 else
//                 {         
//                      tmp->cmd = NULL;
//                     tmp->args[0] = NULL;
//                     write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//                     // return ;
//                 }
//             }
//             z++;
//         }
//         tmp = tmp->next;
//     }
// }

// #include "minishell.h"

// // void    ft_checking_files(t_holder *node)
// // {
// // 	t_holder    *tmp;
// // 	int         i, j, k, check;


// // 	tmp = node;
// // 	i = 0;
// // 	j = 0;
// // 	k = 0;
// // 	while (tmp)
// // 	{
// // 		check  = 0;
// // 		if (tmp->file_in[i])
// // 		{
// // 			tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
// // 			if (tmp->in[i] == -1)
// // 			{
// // 				// ft_putstr_fd(2, in[i]);
// // 				write(2, "such file or directory\n", 24);
// // 				check  = -42;
// // 			}
// // 			i++;
// // 		}
// // 		if (tmp->file_out[j])
// // 		{
// // 			if (check != -42)
// // 			{
// // 				tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
// // 				if (tmp->out[j] == -1)
// // 					write(2, "such file or directory\n", 26);
// // 				j++;
// // 			}
// // 		}
// // 		else if (tmp->append[k])
// // 		{
// // 			tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
// // 			if (tmp->ap[k] == -1)
// // 				write(2, "such file or directory\n", 26);
// // 			k++;
// // 		}
// // 		tmp = tmp->next;
// // 	}
// // }
// int is_ambiguous(char *str)
// {
//     int i = 0;
//     int j = 0;
//     if (str && !str[0])
//         return (1);
//     if (str && str[0] == 32)
//     {
//         while(str[i] && str[i] == 32)
//             i++;
//         if (!str[i])
//             return (1);
//     }
//     i = 0;
//     while (str && str[i])
//     {
//         if (str[i] == ' ')
//             j = 1;
//         if (j == 1 && ft_isalnum(str[i]))
//             return (1);
//         i++;
//     }  
//     return (0);
// }

// int    ft_oppen_files(t_holder *node)
// {
//     t_holder    *tmp;
//     int         i;
//     int         z;
//     int         q;
//     int         b;

//     tmp = node;
//     i = 0;
//     z = 0;
//     q = 0;
//     b = 0;
//     while (tmp && (i < tmp->nbr_file))
//     {
//         if (tmp->outfile_index[b] == i)
//         {
//         if(!is_ambiguous(tmp->file_out[b]))
//         {
//             tmp->out[b] = open(tmp->file_out[b], O_CREAT| O_RDWR, 0644);
//             if (tmp->out[b] == -1)
//             {
//                 write(2, "such file or directory\n", 26);
//                     return (0);
//             }
//             b++;
//         }
//         else
//         {
//             printf("bash: %s: ambiguous redirect\n", tmp->file_out[b]);
//             tmp->out[b] = -7;
//         }
//         }
//         else if (tmp->infile_index[z] == i)
//         {
//             tmp->in[z] = open(tmp->file_in[z], O_RDONLY);
//             if(!is_ambiguous(tmp->file_in[i]))
//             {
//             if (tmp->in[z] == -1)
//             {
//                 write(2, "such file or directory\n", 24);
//                 return (0);
//             }
//             z++;
//             }
//             else
//             {
//                 printf("bash: %s: ambiguous redirect\n", tmp->file_in[z]);
//                  tmp->in[z] = -7;

//             }
//         }
//         else if (tmp->append_index[q] == i)
//         {
//             if(!is_ambiguous(tmp->append[q]))
//             {
//             tmp->ap[q] = open(tmp->append[q], O_CREAT| O_RDWR | O_APPEND, 0644);
//             if (tmp->ap[q] == -1)
//             {
//                 write(2, "such file or directory\n", 26);
//                 return (0);
//             }
//             q++;
//             }
//             else
//             {
//                  printf("bash: %s: ambiguous redirect\n", tmp->append[q]);
//                 tmp->ap[q] = -7;
                
//             }
//         }  
//         i++;
//     }
//     return (1);
// }

// void    ft_checking_files(t_holder *node)
// {
//     t_holder    *tmp;
//     int         i, j, k, check, b, n, z;


//     tmp = node;
//     i = 0;
//     j = 0;
//     b = 0;
//     k = 0;
//     n = 0;
//     z = 0;
//     while (tmp)
//     {
//         check  = 0;
//         while (tmp->file_in[b])
//         {
//             // if (tmp->file_in[i])
//             // {
//                 if(!is_ambiguous(tmp->file_in[i]))
//                 {
//                 tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
//                 if (tmp->in[i] == -1)
//                 {
//                     // ft_putstr_fd(2, in[i]);
//                     write(2, "such file or directory\n", 24);
//                     check  = -42;
//                     // return ;
//                 }
//                 i++;
                
//             }
//             // else
//             // {
//             //             tmp->cmd = NULL;
//             //         tmp->args[0] = NULL;
//             //         write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//             // }
//             b++;
//         }
//         // printf("-------%s-----\n",tmp->file_out[0]);
//         while (tmp->file_out[n])
//         {
//             if (tmp->file_out[j])
//             {
//                 // if (!is_ambiguous(tmp->file_out[j]))
//                 // {
//                 if (check != -42)
//                 {
//                     tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
//                     if (tmp->out[j] == -1)
//                     {
//                         write(2, "such file or directory\n", 26);
//                         // return ;
//                     }
//                     j++;
//                 }
//                 // }
//                 // else
//                 // {
//                 //     tmp->cmd = NULL;
//                 //     tmp->args[0] = NULL;
//                 //     write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//                 // }
//             }
//             n++;
//         }
//         while (tmp->append[z])
//         {
//             if (tmp->append[k])
//             {
//                 if (!is_ambiguous(tmp->append[k]))
//                 {
//                 tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
//                 if (tmp->ap[k] == -1)
//                     write(2, "such file or directory\n", 26);
//                 k++;
//                 }
//                 else
//                 {         
//                      tmp->cmd = NULL;
//                     tmp->args[0] = NULL;
//                     write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
//                     // return ;
//                 }
//             }
//             z++;
//         }
//         tmp = tmp->next;
//     }
// }

#include "minishell.h"

// void    ft_checking_files(t_holder *node)
// {
// 	t_holder    *tmp;
// 	int         i, j, k, check;


// 	tmp = node;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (tmp)
// 	{
// 		check  = 0;
// 		if (tmp->file_in[i])
// 		{
// 			tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
// 			if (tmp->in[i] == -1)
// 			{
// 				// ft_putstr_fd(2, in[i]);
// 				write(2, "such file or directory\n", 24);
// 				check  = -42;
// 			}
// 			i++;
// 		}
// 		if (tmp->file_out[j])
// 		{
// 			if (check != -42)
// 			{
// 				tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
// 				if (tmp->out[j] == -1)
// 					write(2, "such file or directory\n", 26);
// 				j++;
// 			}
// 		}
// 		else if (tmp->append[k])
// 		{
// 			tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
// 			if (tmp->ap[k] == -1)
// 				write(2, "such file or directory\n", 26);
// 			k++;
// 		}
// 		tmp = tmp->next;
// 	}
// }
int is_ambiguous(char *str)
{
    int i = 0;
    int j = 0;
    if (str && !str[0])
        return (1);
    if (str && str[0] == 32)
    {
        while(str[i] && str[i] == 32)
            i++;
        if (!str[i])
            return (1);
    }
    i = 0;
    while (str && str[i])
    {
        if (str[i] == ' ')
            j = 1;
        if (j == 1 && ft_isalnum(str[i]))
            return (1);
        i++;
    }  
    return (0);
}

int    ft_oppen_files(t_holder *node)
{
    t_holder    *tmp;
    int         i;
    int         z;
    int         q;
    int         b;

    tmp = node;
    i = 0;
    z = 0;
    q = 0;
    b = 0;
    while (tmp && (i < tmp->nbr_file))
    {
        if (tmp->outfile_index[b] == i)
        {
        if(!is_ambiguous(tmp->file_out[b]))
        {
            tmp->out[b] = open(tmp->file_out[b], O_CREAT| O_RDWR, 0644);
            if (tmp->out[b] == -1)
            {
                write(2, "such file or directory\n", 26);
                    return (0);
            }
            b++;
        }
        else
        {
            printf("bash: %s: ambiguous redirect\n", tmp->file_out[b]);
            tmp->out[b] = -7;
        }
        }
        else if (tmp->infile_index[z] == i)
        {
            tmp->in[z] = open(tmp->file_in[z], O_RDONLY);
            if(!is_ambiguous(tmp->file_in[i]))
            {
            if (tmp->in[z] == -1)
            {
                write(2, "such file or directory\n", 24);
                return (0);
            }
            z++;
            }
            else
            {
                printf("bash: %s: ambiguous redirect\n", tmp->file_in[z]);
                 tmp->in[z] = -7;

            }
        }
        else if (tmp->append_index[q] == i)
        {
            if(!is_ambiguous(tmp->append[q]))
            {
            tmp->ap[q] = open(tmp->append[q], O_CREAT| O_RDWR | O_APPEND, 0644);
            if (tmp->ap[q] == -1)
            {
                write(2, "such file or directory\n", 26);
                return (0);
            }
            q++;
            }
            else
            {
                 printf("bash: %s: ambiguous redirect\n", tmp->append[q]);
                tmp->ap[q] = -7;
                
            }
        }  
        i++;
    }
    return (1);
}

void    ft_checking_files(t_holder *node)
{
    t_holder    *tmp;
    int         i, j, k, check, b, n, z;


    tmp = node;
    i = 0;
    j = 0;
    b = 0;
    k = 0;
    n = 0;
    z = 0;
    while (tmp)
    {
        check  = 0;
        while (tmp->file_in[b])
        {
            // if (tmp->file_in[i])
            // {
                if(!is_ambiguous(tmp->file_in[i]))
                {
                tmp->in[i] = open(tmp->file_in[i], O_RDONLY);
                if (tmp->in[i] == -1)
                {
                    // ft_putstr_fd(2, in[i]);
                    write(2, "such file or directory\n", 24);
                    check  = -42;
                    // return ;
                }
                i++;
                
            }
            // else
            // {
            //             tmp->cmd = NULL;
            //         tmp->args[0] = NULL;
            //         write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
            // }
            b++;
        }
        // printf("-------%s-----\n",tmp->file_out[0]);
        while (tmp->file_out[n])
        {
            if (tmp->file_out[j])
            {
                // if (!is_ambiguous(tmp->file_out[j]))
                // {
                if (check != -42)
                {
                    tmp->out[j] = open(tmp->file_out[j], O_CREAT| O_RDWR, 0644);
                    if (tmp->out[j] == -1)
                    {
                        write(2, "such file or directory\n", 26);
                        // return ;
                    }
                    j++;
                }
                // }
                // else
                // {
                //     tmp->cmd = NULL;
                //     tmp->args[0] = NULL;
                //     write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
                // }
            }
            n++;
        }
        while (tmp->append[z])
        {
            if (tmp->append[k])
            {
                if (!is_ambiguous(tmp->append[k]))
                {
                tmp->ap[k] = open(tmp->append[k], O_CREAT| O_RDWR | O_APPEND, 0644);
                if (tmp->ap[k] == -1)
                    write(2, "such file or directory\n", 26);
                k++;
                }
                else
                {         
                     tmp->cmd = NULL;
                    tmp->args[0] = NULL;
                    write(2,"ambiguous redirect\n",ft_strlen("ambiguous redirect\n"));
                    // return ;
                }
            }
            z++;
        }
        tmp = tmp->next;
    }
}