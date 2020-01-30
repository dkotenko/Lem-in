# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clala <clala@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 16:58:10 by clala             #+#    #+#              #
#    Updated: 2019/12/29 13:27:10 by clala            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SOURCES = src/ants.c\
src/clala.c \
src/expand_graph.c\
src/find_path_bf.c \
src/find_path_dfs.c \
src/ft_ilen.c \
src/handle_error.c \
src/is_valid_line.c \
src/is_valid_link.c \
src/is_valid_room.c \
src/main.c \
src/print_debug.c \
src/read_input.c \
src/reader.c \
src/t_htable.c \
src/t_htables.c \
src/t_input.c

#src/graph_tech.c\
#src/paths_tech.c\





HEAD = ./src/filler.h
OBJECTS = $(SOURCES:%.c=%.o)
CC = gcc 
FLAGS = -Wall -Wextra -Werror
LEMIN = lem-in
COMP_LIB = make -C libft/
INCLUDES = ./includes/lem-in.h ./libft/libft.h
LIB = libft/libft.a

all: libft $(LEMIN)

$(LEMIN): $(OBJECTS)
	$(CC) $(FLAGS) -o $@  $(OBJECTS) $(LIB)

%.o: %.c $(INCLUDES) $(LIB)
	$(CC) $(FLAGS) -I./ -I./libft/ -c $< -o $@

libft:
	$(COMP_LIB)

clean:	
		/bin/rm -f $(OBJECTS)
		make clean -C libft/


fclean: clean	
		make fclean -C libft/
		/bin/rm -f $(LEMIN)

re: fclean all

.PHONY: all libft clean fclean re
