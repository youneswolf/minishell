SRC = ft_tools.c minishell.c ft_utlils.c ft_give_token.c ft_put_node.c ft_syntax.c ft_red_args.c ft_remove_quote.c ft_holder_node.c ft_checking_files.c redirect_append.c redirect_input.c redirect_output.c
all:
	cc -lreadline -fsanitize=address -g $(SRC) -o minishell