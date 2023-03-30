/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:59:58 by corellan          #+#    #+#             */
/*   Updated: 2023/03/30 11:52:40 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unsupported_2(char *st)
{
	int	i;
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	i = 0;
	while (st[i + 1])
	{
		if (st[i] == '\'' && !quote)
			quote = 1;
		else if (st[i] == '\'' && quote)
			quote = 0;
		if (st[i] == '"' && !d_quote)
			d_quote = 1;
		else if (st[i] == '"' && d_quote)
			d_quote = 0;
		if ((st[i] == '&' && st[i + 1] == '&') && (quote == 0 && d_quote == 0))
			return (1);
		i++;
	}
	return (0);
}

static int	unsupported_1(char *st)
{
	int	i;
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	i = 0;
	while (st[i + 2])
	{
		if (st[i] == '\'' && !quote)
			quote = 1;
		else if (st[i] == '\'' && quote)
			quote = 0;
		if (st[i] == '"' && !d_quote)
			d_quote = 1;
		else if (st[i] == '"' && d_quote)
			d_quote = 0;
		if ((st[i] == '<' && st[i + 1] == '<' && st[i + 2] == '<')
			&& (quote == 0 && d_quote == 0))
			return (1);
		i++;
	}
	return (0);
}

static int	opposite_redir(char *st)
{
	int	i;
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	i = 0;
	while (st[i + 1])
	{
		if (st[i] == '\'' && !quote)
			quote = 1;
		else if (st[i] == '\'' && quote)
			quote = 0;
		if (st[i] == '"' && !d_quote)
			d_quote = 1;
		else if (st[i] == '"' && d_quote)
			d_quote = 0;
		if ((st[i] == '>' && st[i + 1] == '<') && (quote == 0 && d_quote == 0))
			return (1);
		i++;
	}
	return (0);
}

/*
	catch and throw error when it finds:
	- | and || in the beginning of the line
	- && and <<<
	- ><
	- < or > at the end of line
*/
int	catch_errors(char *st)
{	
	if (st[0] == '|')
	{
		ft_error_pipe(st);
		return (1);
	}
	if (unsupported_1(st) || unsupported_2(st))
	{
		ft_error_unsupported();
		return (1);
	}
	if (opposite_redir(st) == 1)
	{
		ft_error_redir(1);
		return (1);
	}
	if (st[ft_strlen(st) - 1] == '<' || st[ft_strlen(st) - 1] == '>' )
	{
		ft_error_redir(2);
		return (1);
	}
	return (0);
}
