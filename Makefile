# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/10/27 11:34:52 by kaheinz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS := -Wall -Werror -Wextra -g
HEADER = ./header
SRCDIR = ./srcs/
OBJDIR := ./build/
LIBFT_DIRECTORY = ./libft
LIBFT = $(LIBFT_DIRECTORY)/libft.a

GREEN = \033[0;32m
RED = \033[0;31m

SRCS = main.c cmd_paths.c tokeniser.c printing.c dollars.c splitter2.c \
		redirecting_vars.c builtins.c buildins2.c execution.c sorting_env.c \
		llist_env.c quote_handling.c sections.c export.c echo.c redirecting.c\
		redirecting2.c heredoc.c delete_section.c free.c execution2.c parent_signals.c init.c exit_status.c dollarizing.c welcome.c

OS = $(shell uname)
ifeq ($(OS), Linux)
FLAGS_OS = -lreadline
endif
ifeq ($(OS), Darwin)
FLAGS_OS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
endif

OBJS = $(SRCS:.c=.o)
OBJECTS_PREF := $(addprefix $(OBJDIR), $(OBJS))

all: $(NAME)

# $(NAME): $(OBJECTS_PREF) $(OBJDIR)
# 	make -C $(LIBFT_DIRECTORY)
# 	$(CC) $(CFLAGS) $(OBJECTS_PREF) $(LIBFT) -I$(HEADER) -o $@ $(OBJS) $(LIBFT) $(FLAGS_OS)

$(NAME):$(OBJECTS_PREF) $(OBJDIR)
	@make -C $(LIBFT_DIRECTORY)
	@$(CC) $(CFLAGS) $(OBJECTS_PREF) $(LIBFT) -I$(HEADER) $(FLAGS) -o $@ $(FLAGS_OS)
	@echo "$(GREEN)$(NAME) was created"

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(OBJECTS_PREF): build/%.o : srcs/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER) -I$(LIBFT_DIRECTORY)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft/
	@echo "$(RED)OBJECTFILES was deleted"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "$(RED)$(NAME) was deleted"

re: fclean all 

.PHONY: all clean fclean re

