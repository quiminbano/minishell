/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:48:36 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 09:31:36 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
