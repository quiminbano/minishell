/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:00:43 by corellan          #+#    #+#             */
/*   Updated: 2023/03/08 17:10:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_echo(char *str)
{
	char	**array;
	int		i;

	i = 2;
	array = ft_custom_split(str);
	if (array[1] == NULL)
	{
		write(1, "\n", 1);
		ft_free_split(array);
		return (3);
	}
	if (ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1]))
		write(1, array[1], ft_strlen(array[1]));
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		i++;
	}
	if (ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1]))
		write(1, "\n", 1);
	ft_free_split(array);
	return (3);
}