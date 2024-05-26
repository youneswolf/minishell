# SRC = ft_tools.c minishell.c ft_utlils.c ft_give_token.c ft_put_node.c ft_syntax.c ft_red_args.c ft_remove_quote.c ft_holder_node.c ft_checking_files.c redirect_append.c redirect_input.c redirect_output.c ft_free.c
# all:
# 	cc -lreadline -fsanitize=address -g $(SRC) -o minishell
# CC = cc 
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 09:42:56 by ybellakr          #+#    #+#              #
#    Updated: 2024/05/24 09:42:57 by ybellakr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc #-fsanitize=address -g
# CC += -Wall -Wextra -Werror
RM = rm -f
NAME = minishell

########## Define ANSI escape codes for colors
GREEN=		\033[32m
YELLOW=		\033[0;33m
RESET=		\033[0m        # No Color

SRC_FILE = minishell.c ft_utlils.c ft_give_token.c ft_put_node.c ft_syntax.c ft_red_args.c ft_free.c\
			 ft_remove_quote.c ft_holder_node.c ft_checking_files.c ft_ctrl_c.c ft_tools.c\
			 redirect_append.c redirect_input.c redirect_output.c ft_her_expand.c ft_remove_here_quote.c\
			 export.c ft_does_matche.c ft_split.c ft_remove_here_quote.c ft_echo.c ft_unset.c ft_env.c ft_cd.c ft_exit.c\
			 ft_pwd.c

SRC_HEADER = minishell.h

OBJS = $(SRC_FILE:.c=.o)

all: $(NAME) 

READLINEDIR = $(shell brew --prefix readline)

%.o: %.c $(SRC_HEADER)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) $(LINKER) $^ -o $@ -L$(READLINEDIR)/lib -lreadline
	@echo "$(GREEN)[====Executable file Compiled Successfully!====]$(RESET)"

clean:
	@echo "$(YELLOW)Removing files...$(RESET)"
	@$(RM) -f $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)[====Object files removed successfully!====]$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing files...$(RESET)"
	@$(RM) -f minishell
	@echo "$(GREEN)[====Object files removed successfully!====]$(RESET)"

re: clean all

.PHONY: clean