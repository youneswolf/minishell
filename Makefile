# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybellakr <ybellakr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/29 21:33:44 by ybellakr          #+#    #+#              #
#    Updated: 2024/04/01 00:34:28 by ybellakr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -lreadline
# CC += -Wall -Wextra -Werror
RM = rm -f
NAME = minishell

########## Define ANSI escape codes for colors
GREEN=		\033[32m
YELLOW=		\033[0;33m
RESET=		\033[0m        # No Color

SRC_FILE = ft_cd.c minishell.c ft_utlils.c ft_give_token.c ft_put_node.c ft_syntax.c ft_red_args.c ft_free.c\
			ft_expand.c ft_env.c ft_remove_quote.c ft_holder_node.c ft_checking_files.c ft_ctrl_c.c

SRC_HEADER = minishell.h

OBJS = $(SRC_FILE:.c=.o)

all: $(NAME) 

# $(NAME): $(OBJS)
# 	@echo "$(YELLOW)Compilation of the files...$(RESET)"
# 	@$(CC) $^ -o $@
# 	@echo "$(GREEN)[====Executable file Compiled Successfully!====]$(RESET)"

READLINEDIR = $(shell brew --prefix readline)

%.o: %.c $(SRC_HEADER)
	@$(CC) -c $< -o $@ -I$(READLINEDIR)/include

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compilation of the Objects files...$(RESET)"
	@$(CC) $(LINKER) $^ -o $@ -L$(READLINEDIR)/lib
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