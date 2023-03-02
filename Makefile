# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:11:10 by corellan          #+#    #+#              #
#    Updated: 2023/03/02 12:29:50 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = test.c

OBJ = test.o

LIBFT = -L libft -lft

FLAGS = -Wall -Wextra -Werror

RL_L = -L ~/.brew/opt/readline/lib -lreadline

RL_I = -I ~/.brew/opt/readline/include/readline

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
		$(MAKE) -C ./libft
		$(CC) $(FLAGS) $(OBJ) $(RL_I) $(LIBFT) $(RL_L) -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) -I. -c $< -o $@

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re