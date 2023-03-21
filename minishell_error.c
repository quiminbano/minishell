/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:59:58 by corellan          #+#    #+#             */
/*   Updated: 2023/03/21 11:03:16 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_pipe(char *str)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
	write(STDERR_FILENO, "token `", 7);
	if (str[1] == '|')
		write(STDERR_FILENO, "||'\n", 4);
	else
		write(STDERR_FILENO, "|'\n", 3);
	return (3);
}
