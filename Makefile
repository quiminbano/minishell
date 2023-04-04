# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:11:10 by corellan          #+#    #+#              #
#    Updated: 2023/04/03 13:48:57 by hel-hosr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c minishell_utils.c minishell_exit.c minishell_argc.c \
minishell_utils_exit.c minishell_echo.c minishell_split_arg.c \
minishell_split_arg_utils.c minishell_split_arg_utils2.c \
minishell_args_list.c minishell_args_utils.c minishell_shortcuts.c \
minishell_pwd_cd.c minishell_env.c minishell_export.c minishell_collect_args.c \
minishell_export_list.c minishell_export_utils.c minishell_unset.c \
minishell_collect_args_utils.c minishell_error.c minishell_run_singleargs.c \
minishell_split_lexer.c minishell_split_lexer_utils.c minishell_lexer_list.c \
minishell_args_lexer.c minishell_utils2.c minishell_process_lexer.c \
minishell_process_args.c minishell_run_singleargs_error.c \
minishell_run_multiargs.c minishell_redirections.c \
minishell_split_lexer_utils2.c minishell_redirections_in.c \
minishell_redirections_out.c minishell_error_printing.c \
hadi_test.c

OBJ = minishell.o minishell_utils.o minishell_exit.o minishell_argc.o \
minishell_utils_exit.o minishell_echo.o minishell_split_arg.o \
minishell_split_arg_utils.o minishell_split_arg_utils2.o \
minishell_args_list.o minishell_args_utils.o minishell_shortcuts.o\
minishell_pwd_cd.o minishell_env.o minishell_export.o minishell_collect_args.o \
minishell_export_list.o minishell_export_utils.o minishell_unset.o \
minishell_collect_args_utils.o minishell_error.o minishell_run_singleargs.o \
minishell_split_lexer.o minishell_split_lexer_utils.o minishell_lexer_list.o \
minishell_args_lexer.o minishell_utils2.o minishell_process_lexer.o \
minishell_process_args.o minishell_run_singleargs_error.o \
minishell_run_multiargs.o minishell_redirections.o \
minishell_split_lexer_utils2.o minishell_redirections_in.o \
minishell_redirections_out.o minishell_error_printing.o \
hadi_test.o


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