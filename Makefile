# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:11:10 by corellan          #+#    #+#              #
#    Updated: 2023/03/04 19:43:31 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c minishell_utils.c minishell_exit.c minishell_argc.c

OBJ = minishell.o minishell_utils.o minishell_exit.o minishell_argc.o

LIBFT = -Llibft -lft

FLAGS = -Wall -Wextra -Werror -g

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