# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalosta- <jalosta-@42abudhabi.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/14 17:23:40 by jalosta-          #+#    #+#              #
#    Updated: 2026/07/14 17:23:40 by jalosta-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a

ARCC		:=	ar -rcs
CC 			:=	gcc
CFLS		:=	-Wall -Wextra -Werror
DBUG		:=  -g

OBJP		:=	objs/

SRCF 		:=	ft_isalpha.c ft_lstadd_back.c ft_lstadd_front.c ft_lstiter.c		\
				ft_lstmap.c	ft_lstsize.c ft_memset.c ft_split.c ft_strjoin.c 		\
				ft_strncmp.c ft_tolower.c ft_atoi.c ft_isascii.c ft_lstclear.c		\
				ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcat.c ft_strnstr.c  	\
				ft_toupper.c ft_bzero.c ft_isdigit.c ft_lstdelone.c ft_memcmp.c   	\
				ft_putendl_fd.c ft_strcmp.c ft_strlcpy.c ft_strrchr.c ft_calloc.c   \
				ft_isprint.c ft_lstlast.c ft_memcpy.c ft_putnbr_fd.c ft_strdup.c    \
				ft_strlen.c ft_strtrim.c ft_isalnum.c ft_itoa.c ft_lstnew.c       	\
				ft_memmove.c ft_putstr_fd.c ft_striteri.c ft_strmapi.c ft_substr.c	\
				ft_putchar.c ft_putnbr.c ft_putstr.c ft_putendl.c
SRCS		:=	$(addprefix $(SRCP), $(SRCF))
OBJS		:=	$(addprefix $(OBJP), $(SRCF:.c=.o))

RM			:=	rm -f

all			:	$(OBJP) $(NAME)

$(OBJP)		:
	mkdir -p $@
$(NAME)		:	$(OBJS)
	$(ARCC) $@ $^
$(OBJP)%.o	:	$(SRCP)%.c
	$(CC) $(CFLS) $(DBUG) -c $< -o $@
clean		:
	$(RM) -r $(OBJP)
fclean		:	clean
	$(RM) $(NAME)
re			:	fclean all