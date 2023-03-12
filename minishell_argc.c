/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/12 11:47:54 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function check many thins. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid. */

int	ft_line_checker(char *s, int *ret, t_env *env)
{
	int	i;

	if (s != (void *)0 && ft_strlen(s) > 0)
		add_history(s);
	if (s == (void *)0)
		handle_ctrlD();
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
	if ((ft_strncmp("echo\0", (s + i), 5) == 0) || \
		(ft_strncmp("echo ", (s + i), 5) == 0) || \
		(ft_strncmp("\"echo\"", (s + i), 7) == 0) || \
		(ft_strncmp("\"echo\" ", (s + i), 7) == 0))
		return (ft_echo(s));
	if ((ft_strncmp("pwd\0", (s + i), 4) == 0) || \
		(ft_strncmp("pwd ", (s + i), 4) == 0) || \
		(ft_strncmp("\"pwd\"", (s + i), 6) == 0) || \
		(ft_strncmp("\"pwd\" ", (s + i), 6) == 0))
		return (ft_pwd());
	if ((ft_strncmp("cd\0", (s + i), 3) == 0) || \
		(ft_strncmp("cd ", (s + i), 3) == 0) || \
		(ft_strncmp("\"cd\"", (s + i), 5) == 0) || \
		(ft_strncmp("\"cd\" ", (s + i), 5) == 0))
		return(ft_cd(s, i, &(*env)));
	if ((ft_strncmp("env\0", (s + i), 4) == 0) || \
		(ft_strncmp("env ", (s + i), 4) == 0) || \
		(ft_strncmp("\"env\"", (s + i), 6) == 0) || \
		(ft_strncmp("\"env\" ", (s + i), 6) == 0))
		return(ft_env(&(*env)));
	return (3);
}
