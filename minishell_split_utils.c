/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:01:50 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 19:19:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_single_quot(char const *str, int *i, int *j)
{
	int	k;

	k = ((*i) + 1);
	while (str[k] != 39 && str[k] != '\0')
		k++;
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
	}
	return (1);
}

int	ft_check_double_quot(char const *str, int *i, int *j)
{
	int	k;

	k = ((*i) + 1);
	while (str[k] != 34 && str[k] != '\0')
		k++;
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
	}
	return (1);
}
