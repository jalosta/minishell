NAME		:=	minishell

CC			:=	cc
CFLS		:=	-Wall -Wextra -Werror
DBUG		:=  -g

INCL		:=	-I includes -I libft
LIBS		:=	-lreadline

SRCF		:=	main.c 						\
				builtins.c 					\
				builtins/cd.c 				\
				builtins/echo.c 			\
				builtins/env.c 				\
				builtins/exit.c 			\
				builtins/export.c 			\
				builtins/pwd.c 				\
				builtins/unset.c 			\
				env.c 						\
				executor/executor.c 		\
				executor/executor_utils.c 	\
				executor/executor_io.c		\
				expander.c 					\
				free.c 						\
				ft_malloc.c 				\
				lexer/lexer.c 				\
				lexer/lexer_utils.c 		\
				parser/parser.c 			\
				parser/parser_utils.c 		\
				parser/parser_heredoc.c 	\
				parser/heredoc_utils.c 		\
				quotes.c
SRCP		:=	srcs/
OBJP		:=	objs/

SRCS		:=	$(addprefix $(SRCP), $(SRCF))
OBJS 		:=	$(addprefix $(OBJP), $(SRCF:.c=.o))

LIBFT		:=	libft
LIBAR		:=	$(LIBFT)/libft.a

RM			:=	rm -f

all			: 	$(NAME)

$(LIBAR)	:
	$(MAKE) -C $(LIBFT)
$(NAME)		: 	$(OBJS) $(LIBAR)
	$(CC) $(CFLS) $(OBJS) $(LIBAR) $(LIBS) -o $@
$(OBJP)%.o	:	$(SRCP)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLS) $(INCL) -c $< -o $@
clean		:
	$(MAKE) -C $(LIBFT) clean
	$(RM) -r $(OBJP)
fclean		: 	clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) $(NAME)
re			: 	fclean all