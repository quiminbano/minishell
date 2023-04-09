/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:20:37 by corellan          #+#    #+#             */
/*   Updated: 2023/04/09 11:24:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipes(int ***fd)
{
	int	i;

	i = 0;
	if ((*fd) == NULL)
		return ;
	while ((*fd)[i] != NULL)
	{
		free((*fd)[i]);
		i++;
	}
	if ((*fd)[i] != NULL)
		free((*fd)[i]);
	if ((*fd) != NULL)
		free((*fd));
}

static void	error_free(int ***fd, int index)
{
	index = index - 1;
	while (index > 0)
	{
		free((*fd)[index]);
		index--;
	}
	free((*fd)[index]);
	free((*fd));
}

int	prepare_pipe_fd(int	***fd, t_m_arg *arg)
{
	(*fd) = (int **)malloc(sizeof(int *) * (arg->n_pipe + 1));
	if ((*fd) == NULL)
		return (-1);
	(*fd)[arg->n_pipe] = NULL;
	while (arg->c_pipe < arg->n_pipe)
	{
		(*fd)[arg->c_pipe] = (int *)malloc(sizeof(int) * 2);
		if ((*fd)[arg->c_pipe] == NULL)
		{
			error_free(&(*fd), arg->c_pipe);
			return (-1);
		}
		(arg->c_pipe) += 1;
	}
	arg->c_pipe = 0;
	return (0);
}