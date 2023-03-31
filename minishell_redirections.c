/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:17:12 by corellan          #+#    #+#             */
/*   Updated: 2023/03/31 14:03:56 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redirections_input(char **ar, t_m_arg *arg)
{
	char	**temp;

	temp = NULL;
	arg->flag_in = 0;
	arg->idx = 0;
	arg->f_err_in = 0;
	while (arg->lexe != NULL && arg->lexe->token == 1)
	{
		arg->flag_in = 1;
		if (arg->idx >= 1)
			close(arg->fdin);
		temp = ft_custom_split(ar[(arg->i) + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1]);
		arg->fdin = open(temp[0], O_RDONLY);
		if (arg->fdin == -1 && arg->f_err_in == 0)
		{
			arg->f_err_in = 1;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
		}
		ft_free_split(temp);
		arg->lexe = arg->lexe->next;
		(arg->idx) += 1;
	}
	if (arg->f_err_in == 1)
		return (1);
	return (0);
}

void	ft_do_redirections(char **ar, t_m_arg *arg)
{
	arg->pid[arg->i] = -1;
	arg->flag_err = 0;
	if (ft_redirections_input(ar, &(*arg)) == 1)
		arg->flag_err = 1;
	if (arg->flag_in == 1)
	{
		dup2(arg->fdin, STDIN_FILENO);
		close(arg->fdin);
	}
	else
	{
		dup2(arg->fdin_next, STDIN_FILENO);
		close(arg->fdin_next);
	}
}