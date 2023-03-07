/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:09:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 12:06:04 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function prints the exit message and it returns a number to notify to the 
main function to return exit.ret (*ret). The (*ret) number is gotten typecasting
the number returned by the function ft_atoll as unsigned char.*/

static int	ft_sucess_return_exit(char **array, char *str, int *ret)
{
	write(2, "exit\n", 5);
	if (ft_strncmp(array[1], "-9223372036854775808", 21) == 0)
	{
		(*ret) = 0;
		ft_free_split(array);
		free(str);
		return (1);
	}
	(*ret) = (unsigned char)ft_atoll(array[1]);
	ft_free_split(array);
	free(str);
	return (1);
}

/*This function prints the proper error case detected in the function 
ft_exit_multiargument and returns a number to the main function. So, with
this number, the main function knows which number should return to exit
the minishell.*/

static int	ft_print_error_exit(char **array, char *str, int error)
{
	write(2, "exit\n", 5);
	if (error == 1)
	{
		write(2, "minishell: exit: ", 17);
		write(2, array[1], ft_strlen(array[1]));
		write(2, ": numeric argument required\n", 28);
		ft_free_split(array);
		free(str);
		return (2);
	}
	if (error == 2)
	{
		write(2, "minishell: exit: ", 17);
		write(2, "too many arguments\n", 19);
		ft_free_split(array);
		return (3);
	}
	return (0);
}

/*This function splits all the arguments in the string, to check the
arguments written after the word exit. First, the function checks if
there are more than one argument after the word exit, and it checks
if there are valid numbers to print the proper error message. On the 
other hand, it check the arguments when there is only one extra argument
after the word exit.*/

static int	ft_exit_multiargument(char *str, int *ret)
{
	char	**array;

	array = ft_split(str, ' ');
	if (array == NULL)
		return (0);
	if (ft_wordcount_argc(str) > 2)
	{
		if (ft_am_i_a_number(array[1]) == 1 || \
			ft_am_i_valid_number(array[1]) == 1)
			return(ft_print_error_exit(array, str, 1));
		else
			return (ft_print_error_exit(array, str, 2));
	}
	else
	{
		if (ft_am_i_a_number(array[1]) == 1 || \
			ft_am_i_valid_number(array[1]) == 1)
			return(ft_print_error_exit(array, str, 1));
		else
			return (ft_sucess_return_exit(array, str, &(*ret)));
	}
	return (0);
}

/*This function check how many arguments were written after the word exit.
if it was just written the word exit, if it was just written the word exit,
the minishell prints in stderr the word exit, and returns a 0. if it has more
arguments, the function returns a value given by the auxiliar function
ft_exit_multiargument.*/

int	ft_exit_check(char *str, int *ret)
{
	if (ft_wordcount_argc(str) == 1)
	{
		write(2, "exit\n", 5);
		free(str);
		return (0);
	}
	else if (ft_wordcount_argc(str) > 1)
		 return (ft_exit_multiargument(str, &(*ret)));
	return (3);
}