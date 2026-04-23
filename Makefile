# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalosta- <jalosta-@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/23 09:48:42 by jalosta-          #+#    #+#              #
#    Updated: 2026/04/23 10:45:49 by jalosta-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -I source/includes -I source/utils/includes

LIBS = -lreadline

LIBFT_SRCS = source/utils/srcs/ft_atoi.c source/utils/srcs/ft_bzero.c source/utils/srcs/ft_calloc.c source/utils/srcs/ft_isalnum.c source/utils/srcs/ft_isalpha.c source/utils/srcs/ft_isascii.c source/utils/srcs/ft_isdigit.c source/utils/srcs/ft_isprint.c source/utils/srcs/ft_itoa.c source/utils/srcs/ft_memchr.c source/utils/srcs/ft_memcmp.c source/utils/srcs/ft_memcpy.c source/utils/srcs/ft_memmove.c source/utils/srcs/ft_memset.c source/utils/srcs/ft_putchar_fd.c source/utils/srcs/ft_putendl_fd.c source/utils/srcs/ft_putnbr_fd.c source/utils/srcs/ft_putstr_fd.c source/utils/srcs/ft_split.c source/utils/srcs/ft_strchr.c source/utils/srcs/ft_strdup.c source/utils/srcs/ft_striteri.c source/utils/srcs/ft_strjoin.c source/utils/srcs/ft_strlcat.c source/utils/srcs/ft_strlcpy.c source/utils/srcs/ft_strlen.c source/utils/srcs/ft_strmapi.c source/utils/srcs/ft_strncmp.c source/utils/srcs/ft_strnstr.c source/utils/srcs/ft_strrchr.c source/utils/srcs/ft_strtrim.c source/utils/srcs/ft_substr.c source/utils/srcs/ft_tolower.c source/utils/srcs/ft_toupper.c
LIBFT_SRCS += source/utils/srcs/ft_lstnew.c source/utils/srcs/ft_lstsize.c source/utils/srcs/ft_lstlast.c source/utils/srcs/ft_lstadd_back.c source/utils/srcs/ft_lstdelone.c source/utils/srcs/ft_lstclear.c

SRCS = source/srcs/main.c $(LIBFT_SRCS)

OBJ_DIR = objs

OBJS = $(SRCS:source/srcs/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: source/srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ 	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re