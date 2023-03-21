# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:11:10 by corellan          #+#    #+#              #
#    Updated: 2023/03/21 10:10:28 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c minishell_utils.c minishell_exit.c minishell_argc.c \
minishell_utils_exit.c minishell_echo.c minishell_split_arg.c \
minishell_split_arg_utils.c minishell_split_arg_utils2.c \
minishell_args_list.c minishell_args_utils.c minishell_shortcuts.c \
minishell_pwd_cd.c minishell_env.c minishell_export.c minishell_collect_args.c \
minishell_export_list.c minishell_export_utils.c minishell_unset.c \
minishell_collect_args_utils.c minishell_error.c

OBJ = minishell.o minishell_utils.o minishell_exit.o minishell_argc.o \
minishell_utils_exit.o minishell_echo.o minishell_split_arg.o \
minishell_split_arg_utils.o minishell_split_arg_utils2.o \
minishell_args_list.o minishell_args_utils.o minishell_shortcuts.o\
minishell_pwd_cd.o minishell_env.o minishell_export.o minishell_collect_args.o \
minishell_export_list.o minishell_export_utils.o minishell_unset.o \
minishell_collect_args_utils.o minishell_error.o

LIBFT = -Llibft -lft

FLAGS = -Wall -Wextra -Werror

RL_L = -lreadline -L ~/.brew/opt/readline/lib

RL_I = -I ~/.brew/opt/readline/include

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(RL_L) $(RL_I) -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(RL_I) -I. -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re