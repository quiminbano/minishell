/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:28:35 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 18:17:59 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function checks if the numbers written as an argument are overflowed or
not.*/

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

/*This function checks if the string represents a number or not. For that, it
uses a counter(i) to count how many digits has the number before finding weird
characters. If this counter(i) matchs with the length of the string, it means
that the string represents a number and the function returns 0. But, if the 
counter(i) is less than the length of the string, it means that it is not a 
valid number and it returns 1.*/

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

/*This function converts a string in a long long number. it doesn't work with
LONG_LONG_MIN.*/

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
