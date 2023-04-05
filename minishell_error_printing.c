/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_printing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:01:30 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/03 11:42:38 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_pipe(int err)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
	write(STDERR_FILENO, "token `", 7);
	if (err == 2)
		write(STDERR_FILENO, "||'\n", 4);
	else if (err == 1)
		write(STDERR_FILENO, "|'\n", 3);
	return (1);
}

int	ft_error_redir(int err, char *st, int i)
{
	if (err == 1)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
		write(STDERR_FILENO, "token `", 7);
		if (st[i + 2] == '<' && st[i + 3] != '<')
			write(STDERR_FILENO, "<<'\n", 4);
		else if (st[i + 2] == '<' && st[i + 3] == '<')
			write(STDERR_FILENO, "<<<'\n", 5);
		else
			write(STDERR_FILENO, "<'\n", 3);
	}
	else if (err == 2)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected ", 40);
		write(STDERR_FILENO, "token `", 7);
		write(STDERR_FILENO, "newline'\n", 9);
	}
	return (1);
}

int	ft_error_unsupported(void)
{
	write(STDERR_FILENO,
		"\nNOT SUPPORTED.\nPlease upgrade to premium version.\n\n", 52);
	return (1);
}
