# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/09/26 11:46:26 by ksura@student.42 ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c cmd_paths.c tokeniser.c printing.c dollars.c splitter2.c \
		directing_vars.c buildins.c execution.c sorting_env.c llist_env.c


LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

OS = $(shell uname)
ifeq ($(OS), Linux)
FLAGS_OS = -lreadline
endif
ifeq ($(OS), Darwin)
FLAGS_OS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
endif


$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FLAGS_OS)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all 

.PHONY: all clean fclean re

