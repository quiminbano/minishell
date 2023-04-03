/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections_in.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:14:43 by corellan          #+#    #+#             */
/*   Updated: 2023/04/03 10:15:27 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirections_input(char **ar, t_m_arg *arg)
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
