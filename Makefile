SRC = minishell.c ft_utlils.c ft_give_token.c ft_put_node.c ft_syntax.c ft_red_args.c ft_expand.c ft_env.c ft_remove_quote.c ft_holder_node.c ft_checking_files.c redirect_append.c redirect_input.c redirect_output.c get_next_line/get_next_line_utils_bonus.c get_next_line/get_next_line_bonus.c
all:
	cc -lreadline -fsanitize=address -g $(SRC) -o minishell