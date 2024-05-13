NAME = minishell
CC = cc
READLINE_PATH = /Users/$(USER)/.brew/opt/readline
CFLAGS = -Wall -Wextra -Werror -Imain -I$(READLINE_PATH)/include
LDFLAGS = -lreadline -lhistory -L $(READLINE_PATH)/lib

SRCS = 	main/main.c \
		main/utils_free.c \
		main/utils.c \
		main/signal.c \
		main/init_env.c \
		srcs/lexer/lex.c \
		srcs/lexer/lex_more.c \
		srcs/parser/par.c \
		srcs/parser/par_utils.c \
		srcs/execute/exe_fd.c \
		srcs/execute/exe_heredoc.c \
		srcs/execute/exe_process.c \
		srcs/execute/exe_utils.c \
		srcs/execute/exe.c \
		srcs/expander/exp_red.c \
		srcs/expander/exp_utils.c \
		srcs/expander/exp_cmd.c \
		srcs/expander/exp_cmd_msplit.c \
		node/node_addback.c \
		node/node_clear.c \
		node/node_delone.c \
		node/node_iter.c \
		node/node_last.c \
		node/node_nb.c \
		node/node_new.c \
		builtins/builtins_utils.c \
		builtins/builtins.c \
		builtins/ft_cd.c \
		builtins/ft_env.c \
		builtins/ft_echo.c \
		builtins/ft_exit.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		builtins/ft_export.c \
		builtins/ft_export_only.c

INCLUDE =	main/main.h

LIBFT = libft/

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) libft/libft.a -o $(NAME) $(OBJS)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re