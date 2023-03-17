/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:00:43 by corellan          #+#    #+#             */
/*   Updated: 2023/03/17 15:05:00 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function checks if the second argument of the command echo is indeed
the option -n (-nn, -nnn, -nnnn, etc.) or not.*/

static int	ft_second_arg_echo_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	return (i);
}

/*This function prints spaces between the strings in the split if necessary.
First, we skip the first member of the list, because it marks the position
of the space character between the word echo and the second argument. if the
second argument is not the -n argument( or -nn or -nnn, etc), the shell prints
the first word. But if it is the -n argument, we move to the next member of the
list. The reason to do that is because, this number represent the space
character between the option -n and the first word. After that, there is a 
while loop that helps to print an space character before array[i] if the
member of the list (pos) matchs with the value of the index i.*/

static void	ft_echo_aux(char **array, int i)
{
	if (ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1]))
	{
		write(1, array[1], ft_strlen(array[1]));
		write(1, " ", 1);
	}
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		i++;
		if (array[i] != NULL)
			write(1, " ", 1);
	}
}

/*This function checks every argument to use when we call echo through the
minishell. First, we check if there is just one argument (if we write just
echo in the minishell). After that, in t_echo list, we save the number or
arguments when it is necessary to print an space character. We can achieve
that with the function ft_wordcount_echo. In the function ft_echo_aux, we
prepare the system to print the text written. With the function ft_second_arg
_echo_check, we check if we need to print a skip line(\n) or not, adding
the opcion -n, -nn, -nnn, etc. ft_free_split and ft_free_list free the
split and the echo list respectively.*/

int	ft_echo(char **array)
{
	int	i;

	i = 2;
	if (array[1] == NULL)
	{
		write(1, "\n", 1);
		ft_free_split(array);
		return (3);
	}
	ft_echo_aux(array, i);
	if ((ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1])) || \
		(ft_strlen(array[1]) == 0))
		write(1, "\n", 1);
	ft_free_split(array);
	return (3);
}
