/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:17:12 by corellan          #+#    #+#             */
/*   Updated: 2023/04/04 16:23:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_process_reout(t_m_arg *arg)
{
	if (arg->lexe != NULL && arg->lexe->token == 5)
	{
		if (pipe(arg->fd) == -1)
		{
			perror("minishell");
			(arg->i) = arg->len;
			return (3);
		}
		arg->fdout_pipe = arg->fd[1];
		arg->fdin_pipe = arg->fd[0];
		arg->lexe = arg->lexe->next;
	}
	if (arg->flag_out == 1 || arg->flag_end == 1)
	{
		write(arg->fdout_pipe, "\0", 1);
		close(arg->fdout_pipe);
		dup2(arg->fdout, STDOUT_FILENO);
		close(arg->fdout);
	}
	else
	{
		dup2(arg->fdout_pipe, STDOUT_FILENO);
		close(arg->fdout_pipe);
	}
	return (0);
}

static void	ft_process_rein(t_m_arg *arg)
{
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

void	ft_do_redirections(char **ar, t_m_arg *arg)
{
	arg->n_redir = ft_c_redic_in_a_row(&(arg->lexe));
	arg->lex_size = ft_listsize_lexer(&(arg->lexe));
	arg->flag_err = 0;
	arg->flag_in = 0;
	arg->flag_out = 0;
	arg->flag_end = 0;
	arg->idx = 0;
	arg->fdout = dup(arg->tmpout);
	dup2(arg->tmpout, STDOUT_FILENO);
	while (arg->idx < arg->n_redir)
	{
		ft_redirections_input(ar, &(*arg));
		ft_redirections_output(ar, &(*arg));
		ft_redirect_out_append(ar, &(*arg));
		arg->lexe = arg->lexe->next;
		(arg->idx)++;
		arg->pid[arg->i + arg->idx] = -1;
	}
	ft_process_rein(&(*arg));
}
