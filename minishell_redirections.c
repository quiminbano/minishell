/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:17:12 by corellan          #+#    #+#             */
/*   Updated: 2023/04/01 15:54:46 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_out_append(char **ar, t_m_arg *arg)
{
	char	**temp;

	temp = NULL;
	if (arg->lexe->token == 4 && arg->flag_err == 0)
	{
		if (arg->flag_out == 1)
			close(arg->fdout);
		temp = ft_custom_split(ar[(arg->i) + arg->idx + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1 + arg->idx]);
		arg->fdout = open(temp[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (arg->fdout == -1 && arg->flag_err == 0)
		{
			arg->flag_err = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_free_split(temp);
		arg->flag_out = 1;
	}
}

static void	ft_redirections_output(char **ar, t_m_arg *arg)
{
	char	**temp;

	temp = NULL;
	if (arg->lexe->token == 2 && arg->flag_err == 0)
	{
		if (arg->flag_out == 1)
			close(arg->fdout);
		temp = ft_custom_split(ar[(arg->i) + arg->idx + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1 + arg->idx]);
		arg->fdout = open(temp[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (arg->fdout == -1 && arg->flag_err == 0)
		{
			arg->flag_err = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_free_split(temp);
		arg->flag_out = 1;
	}
}

static void	ft_redirections_input(char **ar, t_m_arg *arg)
{
	char	**temp;

	temp = NULL;
	if (arg->lexe->token == 1 && arg->flag_err == 0)
	{
		if (arg->flag_in == 1)
			close(arg->fdin);
		temp = ft_custom_split(ar[(arg->i) + arg->idx + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1 + arg->idx]);
		arg->fdin = open(temp[0], O_RDONLY);
		if (arg->fdin == -1 && arg->flag_err == 0)
		{
			arg->flag_err = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_free_split(temp);
		arg->flag_in = 1;
	}
}

void	ft_do_redirections(char **ar, t_m_arg *arg)
{
	arg->n_redir = ft_c_redic_in_a_row(&(arg->lexe));
	arg->flag_err = 0;
	arg->flag_in = 0;
	arg->flag_out = 0;
	arg->flag_end = 0;
	arg->idx = 0;
	arg->pid[arg->i] = -1;
	while (arg->idx < arg->n_redir)
	{
		ft_redirections_input(ar, &(*arg));
		ft_redirections_output(ar, &(*arg));
		ft_redirect_out_append(ar, &(*arg));
		arg->lexe = arg->lexe->next;
		(arg->idx)++;
		arg->pid[arg->i + arg->idx] = -1;
	}
	if (arg->flag_in == 1)
	{
		dup2(arg->fdin, STDIN_FILENO);
		close(arg->fdin);
	}
	else
	{
		dup2(arg->fdin_pipe, STDIN_FILENO);
		close(arg->fdin_pipe);
	}
}
