/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:17:12 by corellan          #+#    #+#             */
/*   Updated: 2023/03/30 16:54:08 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirections_input(char **ar, t_m_arg *arg)
{
	char	**temp;

	temp = NULL;
	arg->flag_in = 0;
	if (arg->lexe->token == 1)
	{
		arg->flag_in = 1;
		temp = ft_custom_split(ar[(arg->i) + 1]);
		temp = ft_process_arg(temp, ar[(arg->i) + 1]);
		arg->fdin = open(temp[0], O_RDONLY);
		if (arg->fdin == -1)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, temp[0], ft_strlen(temp[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			ft_free_split(temp);
			return (1);
		}
		ft_free_split(temp);
	}
	return (0);
}