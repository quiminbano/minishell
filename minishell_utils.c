/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:48:36 by corellan          #+#    #+#             */
/*   Updated: 2023/03/16 15:38:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function returns the index of a string where a word (needle) is 
contained. If the word doesn't exist, it returns the ammount of strings in the
array.*/

int	ft_find_word_array(char **array, char *needle)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL && \
		(ft_strncmp(needle, array[i], ft_strlen(needle)) != 0))
		i++;
	return (i);
}

/*This function returns the ammount of strings that a 2D-array has.*/

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
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
