NAME		:=	minishell

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror

INCLUDES	:=	-I source/includes
LIBS		:=	-lreadline

SRCS        :=  source/srcs/builtins.c source/srcs/env.c source/srcs/executor.c \
                source/srcs/ft_malloc.c source/srcs/parser.c source/srcs/main.c \
                source/srcs/expander.c source/srcs/free.c source/srcs/lexer.c \
                source/srcs/heredoc_utils.c source/srcs/quotes.c \
                source/srcs/executor_utils.c source/srcs/executor_io.c \
                source/srcs/parser_utils.c source/srcs/parser_heredoc.c \
                source/srcs/lexer_utils.c
LIBFT_DIR	:=	source/srcs/libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

RM			:=	rm -f

all: 			$(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(NAME): 		$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $@
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)
fclean: 		clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
re: 			fclean all
