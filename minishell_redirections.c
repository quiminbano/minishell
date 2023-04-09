/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:17:12 by corellan          #+#    #+#             */
/*   Updated: 2023/04/09 11:55:44 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	incorrect_redirect_aux(t_m_arg *arg)
{
	int	fd[RE_OUT];

	if (pipe(fd) == -1)
	{
		perror("minishell");
		return ;
	}
	write(fd[1], "\0", 1);
	close(fd[1]);
	arg->fdin = fd[0];
	arg->flag_in = 1;
}

static void	ft_incorrect_redirect(char **ar, t_m_arg *arg)
{
	char	**temp;
	int		ferr;

	temp = NULL;
	if (arg->lexe->token == 6 && arg->flag_err == 0)
	{
		temp = ft_custom_split(ar[(arg->i) + arg->idx + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1 + arg->idx]);
		ferr = open(temp[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (ferr == -1 && arg->flag_err == 0)
		{
			arg->flag_err = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_free_split(temp);
		close(ferr);
		incorrect_redirect_aux(&(*arg));
	}
}

void	close_fd(t_m_arg *arg)
{
	close(arg->fdin);
	if (arg->flag_pipe == 1)
		close(arg->fdout_pipe);
	if (arg->flag_out == 1)
		close(arg->fdout);
	if ((arg->i + arg->idx) == (arg->len - 1))
		close(arg->tmpout);
}

int	ft_process_pipe(t_m_arg *arg)
{
	if (arg->flag_in == 0 && arg->i != 0)
		arg->fdin = arg->fd[arg->c_pipe - 1][0];
	else if (arg->flag_in == 1 && arg->i != 0)
		close(arg->fd[arg->c_pipe - 1][0]);
	if (arg->c_pipe < arg->n_pipe)
	{
		arg->flag_pipe = 1;
		if (pipe(arg->fd[arg->c_pipe]) == -1)
		{
			perror("minishell");
			ft_free_pipes(&(arg->fd));
			(arg->i) = arg->len;
			return (3);
		}
		arg->fdout_pipe = arg->fd[(arg->c_pipe)][1];
		(arg->c_pipe) += 1;
		arg->lexe = arg->lexe->next;
	}
	return (0);
}

void	ft_do_redirections(char **ar, t_m_arg *arg)
{
	arg->n_redir = ft_c_redic_in_a_row(&(arg->lexe));
	arg->lex_size = size_lex(&(arg->lexe));
	arg->flag_err = 0;
	arg->flag_in = 0;
	arg->flag_out = 0;
	arg->flag_pipe = 0;
	arg->idx = 0;
	if (arg->i == 0)
		arg->pid[0] = 0;
	while (arg->idx < arg->n_redir)
	{
		ft_redirections_input(ar, &(*arg));
		ft_redirections_output(ar, &(*arg));
		ft_reredirect_input(ar, &(*arg));
		ft_redirect_out_append(ar, &(*arg));
		ft_incorrect_redirect(ar, &(*arg));
		arg->lexe = arg->lexe->next;
		(arg->idx)++;
		arg->pid[arg->i + arg->idx] = -1;
	}
}
