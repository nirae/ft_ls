# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/14 16:48:13 by ndubouil          #+#    #+#              #
#    Updated: 2018/09/25 18:56:00 by ndubouil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binaries and Flags

CC		=	/usr/bin/gcc
AR		=	/usr/bin/ar
RM		=	/bin/rm
CFLAGS	=	-Wall -Wextra -Werror

# Directories

LIBFT	=	./libft/
ILIBFT	=	./$(LIBFT)includes/
H		=	./includes/
SRC		=	./src/

#  Files

HFILES	=	$(H)ft_ls.h
MAIN	=	$(SRC)main.c
SRCS	=	$(SRC)sort/get_sort_func.c								\
			$(SRC)sort/basic_sort.c									\
			$(SRC)sort/mtime_nano_sort.c							\
			$(SRC)sort/mtime_sort.c									\
			$(SRC)sort/atime_nano_sort.c							\
			$(SRC)sort/atime_sort.c									\
			$(SRC)sort/f_sort.c										\
			$(SRC)parsing.c											\
			$(SRC)trees_tools.c										\
			$(SRC)errors.c											\
			$(SRC)ft_ls.c											\
			$(SRC)printing/print_tree.c								\
			$(SRC)printing/print_recursive.c						\
			$(SRC)printing/print_main_args.c						\
			$(SRC)printing/ls_printer.c								\
			$(SRC)printing/print_long_format/getters.c				\
			$(SRC)printing/print_long_format/print_time.c			\
			$(SRC)printing/print_long_format/print_long_format.c

OBJ		=	$(patsubst %.c,%.o,$(SRCS))
# Name

NAME	=	ft_ls

.PHONY: all clean fclean re

all:		$(NAME)
		@true

$(NAME):	$(OBJ) $(MAIN) $(HFILES) $(LIBFT) Makefile
		@echo "Compiling Libft ..."
		@make -C $(LIBFT)
		@echo "Building $(NAME) ..."
		@$(CC) $(CFLAGS) $(MAIN) $(OBJ) -I$(H) -I$(ILIBFT) -L$(LIBFT) -lft -o $(NAME)
		@echo "I'm READY"

%.o: 		%.c
		@echo "Creating $@ ..."
		@$(CC) $(CFLAGS) -I$(H) -I$(ILIBFT) -c $< -o $@

clean:
		@echo "Cleaning Objs ..."
		@$(RM) -f $(OBJ)
		@echo "Cleaning Libft Objs ..."
		@make clean -C $(LIBFT)

fclean:		clean
		@echo "Cleaning $(NAME) exec"
		@$(RM) -f $(NAME)
		@echo "Cleaning libft exec"
		@make fclean -C $(LIBFT)

re:			fclean all
