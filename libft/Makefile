# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edrowzee <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019\06\17 13:45:56 by edrowzee          #+#    #+#              #
#    Updated: 2019/09/12 16:19:20 by edrowzee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
HEADERS = libft.h
FILES = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memalloc.c ft_memcpy.c ft_memdel.c ft_memchr.c \
ft_memccpy.c ft_memcmp.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putchar.c ft_putendl_fd.c ft_putendl.c ft_putnbr_fd.c ft_putnbr.c \
ft_putstr_fd.c ft_putstr.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strncmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncpy.c \
ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strstr.c \
ft_strsub.c ft_strtrim.c ft_toupper.c ft_tolower.c ft_itoa.c \
ft_atoi.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_btree_insert_data.c \
ft_btree_create_node.c ft_btree_apply_suffix.c ft_btree_apply_prefix.c \
ft_btree_apply_infix.c get_next_line.c

OBJECTS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	gcc $(CCFLAGS) -c $< -I.

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -rf  $(NAME)

re: fclean all

.PHONY: all clean fclean re
