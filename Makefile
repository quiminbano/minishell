# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:11:10 by corellan          #+#    #+#              #
#    Updated: 2023/03/06 08:43:27 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c minishell_utils.c minishell_exit.c minishell_argc.c \
minishell_utils_exit.c

OBJ = minishell.o minishell_utils.o minishell_exit.o minishell_argc.o \
minishell_utils_exit.o

LIBFT = -Llibft -lft

FLAGS = -Wall -Wextra -Werror

RL_L = -lreadline -L /opt/homebrew/opt/readline/lib

RL_I = -I /opt/homebrew/opt/readline/include

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