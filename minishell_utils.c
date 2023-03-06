/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:48:36 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 18:03:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function counts how many spaces are before the first word written in
a command.*/

int	ft_count_space(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
	{
		i++;
	}
	return (i);
}

/*This function checks if there are special characters in the command written.
it works for now with the command exit.*/

int	ft_check_symbols(char const *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '|') || (str[i] == '<') || (str[i] == '>'))
			j++;
		i++;
	}
	return (j);
}

/*This function counts how many arguments are in a line. For now, it works with
the command exit.*/

int	ft_wordcount_argc(char const *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ') && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}
