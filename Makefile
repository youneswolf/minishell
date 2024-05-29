# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 09:42:56 by ybellakr          #+#    #+#              #
#    Updated: 2024/05/29 13:57:42 by ybellakr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC += -Wall -Wextra -Werror
RM = rm -f
NAME = minishell

########## Define ANSI escape codes for colors
GREEN=		\033[32m
YELLOW=		\033[0;33m
RESET=		\033[0m        # No Color

SRC_FILE =	parsing/minishell.c execution/ft_utlils.c parsing/ft_give_token.c parsing/ft_put_node.c parsing/ft_syntax.c parsing/ft_red_args.c parsing/ft_free.c\
			 parsing/ft_remove_quote.c parsing/ft_holder_node.c parsing/ft_checking_files.c parsing/ft_ctrl_c.c execution/ft_tools.c\
			 execution/redirect_append.c execution/redirect_input.c execution/redirect_output.c execution/ft_her_expand.c execution/ft_remove_here_quote.c\
			 built_in//export.c parsing/ft_does_matche.c execution/ft_split.c built_in/ft_echo.c built_in/ft_unset.c built_in/ft_env.c built_in/ft_cd.c built_in/ft_exit.c\
			 built_in/ft_pwd.c parsing/ft_add_space.c parsing/ft_checking_files.c parsing/ft_ctrl_c.c execution/ft_expand.c parsing/ft_is_built_in.c\
			 parsing/ft_signals.c parsing/ft_utils.c parsing/skip_expand.c execution/ft_execution.c parsing/ft_files_utiles.c\
			 parsing/ft_matche_utils.c parsing/ft_holder1.c parsing/ft_holder2.c parsing/ft_holder3.c parsing/ft_holder4.c parsing/ft_put_utils.c \
			 built_in/export_1.c built_in/export_2.c built_in/export_3.c built_in/export_4.c execution/ft_her_expand_1.c execution/ft_her_expand_2.c \
			 execution/ft_tools_1.c execution/ft_tools_2.c execution/ft_tools_3.c execution/ft_tools_4.c execution/ft_tools_5.c execution/ft_tools_6.c execution/ft_tools_7.c \
			 execution/execution_1.c execution/execution_2.c execution/execution_3.c execution/execution_4.c execution/execution_5.c \
			 execution/execution_6.c execution/execution_7.c execution/execution_8.c built_in/ft_exit_utils.c

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