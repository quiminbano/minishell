/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:09:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/04 19:48:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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