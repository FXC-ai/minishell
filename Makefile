SRCS	= $(addprefix srcs/, main.c ms_pipe.c signal.c parse_args.c lexer.c ft_split_lexer.c redirection.c utils.c)

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= minishell

INCLUDE = includes

#$@ = all, $< = server / client

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C libft
	$(CC) -o $(NAME) $(OBJS) -Llibft -lft -I $(INCLUDE) -lreadline -L ../../.brew/opt/readline/lib -I ../../.brew/opt/readline/include

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	${RM}  $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re