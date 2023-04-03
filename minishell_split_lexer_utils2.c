/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_lexer_utils2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:51:03 by corellan          #+#    #+#             */
/*   Updated: 2023/03/31 09:58:55 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_dash_split_lexer(const char *str, int *i, int *j)
{
	if (str[(*i)] == '\\' && check_char(str, ((*i) + 1)) == 1)
	{
		(*i) += 1;
		if (check_char(str, ((*i) + 1)) == 1)
			(*j) += 1;
		(*i) += 1;
		return (1);
	}
	return (0);
}
