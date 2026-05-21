NAME		:=	minishell

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror

INCLUDES	:=	-I source/includes
LIBS		:=	-lreadline

SRCS		:=	source/srcs/main.c

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
	$(RM) -r $(OBJ_DIR)
fclean: 		clean
	$(RM) $(NAME)
re: 			fclean all

.PHONY: 		all clean fclean re
