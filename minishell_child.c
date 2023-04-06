/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:55:01 by corellan          #+#    #+#             */
/*   Updated: 2023/04/06 15:32:51 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(char *path, char **cmd, t_env *env)
{
	if (execve(path, cmd, env->env) < 0)
	{
		free(path);
		ft_free_split(cmd);
		write(STDERR_FILENO, "minishell: : command not found\n", 31);
		exit (127);
	}
}
