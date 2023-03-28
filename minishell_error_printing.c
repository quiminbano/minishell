/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_printing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:01:30 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/28 14:38:44 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_pipe(char *str)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
	write(STDERR_FILENO, "token `", 7);
	if (str[1] == '|')
		write(STDERR_FILENO, "||'\n", 4);
	else
		write(STDERR_FILENO, "|'\n", 3);
}

void	ft_error_redir(int err)
{
	if (err == 1)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
		write(STDERR_FILENO, "token `", 7);
		write(STDERR_FILENO, "<'\n", 3);
	}
	else if (err == 2)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
		write(STDERR_FILENO, "token `", 7);
		write(STDERR_FILENO, "newline'\n", 9);
	}
}

void	ft_error_unsupported(void)
{
	write(STDERR_FILENO, "NOT SUPPORTED.\nPlease upgrade to premium version.\n", 50);
}
