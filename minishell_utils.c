/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:48:36 by corellan          #+#    #+#             */
/*   Updated: 2023/03/04 19:43:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_am_i_valid_number(char const *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (0);
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] <= 57 && str[i] >= 48)
	{
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	if (num < 0)
		return (1);
	return (0);
}

int	ft_am_i_a_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	while ((str[i] <= 57 && str[i] >= 48))
		i++;
	if (i < ft_strlen(str))
		return (1);
	return (0);
}

long long	ft_atoll(char const *str)
{
	int			i;
	long long	number;
	long long	neg;

	i = 0;
	neg = 1;
	number = 0;
	while (str[i] == ' ' || (str[i] >= 8 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] <= 57 && str[i] >= 48)
	{
		number *= 10;
		number += (str[i++] - '0');
	}
	if ((number < 0) && (neg == -1))
		return (0);
	if ((number < 0) && (neg == 1))
		return (-1);
	return ((neg * number));
}

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