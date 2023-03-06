/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 09:06:05 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_i_need_to_leave(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
}

int	ft_line_checker(char *s, int *ret)
{
	int	i;

	if (s != (void *)0 && ft_strlen(s) > 0)
		add_history(s);
	if (s == (void *)0)
	{
		ft_i_need_to_leave();
		exit(0);
	}
	i = ft_count_space(s);
	if ((ft_strncmp("exit\0", (s + i), 5) == 0) || \
		(ft_strncmp("exit ", (s + i), 5) == 0) || \
		(ft_strncmp("\"exit\"", (s + i), 7) == 0) || \
		(ft_strncmp("\"exit\" ", (s + i), 7) == 0))
	{
		if (ft_check_symbols(s) == 0)
			return (ft_exit_check(s, &(*ret)));
		else
			return (3);
	}
	return (3);
}