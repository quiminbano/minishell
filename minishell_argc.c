/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 12:32:16 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is an answer to press ctrl + D. Not well implemented yet.*/

static void	ft_i_need_to_leave(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
}

/*This function check many thins. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid. */

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