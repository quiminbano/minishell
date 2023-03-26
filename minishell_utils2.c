/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:03:55 by corellan          #+#    #+#             */
/*   Updated: 2023/03/23 17:04:49 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_w_space(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (i);
}
