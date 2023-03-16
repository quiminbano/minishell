/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:23:24 by corellan          #+#    #+#             */
/*   Updated: 2023/03/15 10:42:52 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is similar to ft_check_single_quot. The difference in this one
is, ft_check_s_quot_echo add the value of (*j) to the t_echo linked list if
there is an space after the ' character in the string splitted. */

int	ft_check_s_quot_echo(char const *str, int *i, int *j, t_echo **e)
{
	int	k;

	k = ((*i) + 1);
	if (str[k] == 39)
		return (0);
	while (str[k] != 39 && str[k] != '\0')
	{
		if (str[k] == '\\' && str[k + 1] == 39)
			k++;
		k++;
	}
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_echo(&(*e), (*j));
	}
	return (1);
}

/*This function is similar to ft_check_single_quot. The difference in this one
is, ft_check_s_quot_echo add the value of (*j) to the t_echo linked list if
there is an space after the " character in the string splitted. */

int	ft_check_d_quot_echo(char const *str, int *i, int *j, t_echo **e)
{
	int	k;

	k = ((*i) + 1);
	if (str[k] == 34)
		return (0);
	while (str[k] != 34 && str[k] != '\0')
	{
		if (str[k] == '\\' && str[k + 1] == 34)
			k++;
		k++;
	}
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_echo(&(*e), (*j));
	}
	return (1);
}
