/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/14 16:56:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function check many thins. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid. */

int	ft_line_checker(char *st, int *ret, t_env *env)
{
	int		i;
	char	**array;

	if (st != (void *)0 && ft_strlen(st) > 0)
		add_history(st);
	if (st == (void *)0)
		return(handle_ctrlD(st));
	array = ft_custom_split(st);
	array = ft_process_line(array, st);
	i = ft_count_space(st);
	if ((ft_strncmp("exit\0", (st + i), 5) == 0) || \
		(ft_strncmp("exit ", (st + i), 5) == 0) || \
		(ft_strncmp("\"exit\"", (st + i), 7) == 0) || \
		(ft_strncmp("\"exit\" ", (st + i), 7) == 0))
	{
		if (ft_check_symbols(st) == 0)
			return (ft_exit_check(st, &(*ret)));
		else
			return (3);
	}
	if ((ft_strncmp("echo\0", (st + i), 5) == 0) || \
		(ft_strncmp("echo ", (st + i), 5) == 0) || \
		(ft_strncmp("\"echo\"", (st + i), 7) == 0) || \
		(ft_strncmp("\"echo\" ", (st + i), 7) == 0))
		return (ft_echo(st));
	if ((ft_strncmp("pwd\0", (st + i), 4) == 0) || \
		(ft_strncmp("pwd ", (st + i), 4) == 0) || \
		(ft_strncmp("\"pwd\"", (st + i), 6) == 0) || \
		(ft_strncmp("\"pwd\" ", (st + i), 6) == 0))
		return (ft_pwd());
	if ((ft_strncmp("cd\0", (st + i), 3) == 0) || \
		(ft_strncmp("cd ", (st + i), 3) == 0) || \
		(ft_strncmp("\"cd\"", (st + i), 5) == 0) || \
		(ft_strncmp("\"cd\" ", (st + i), 5) == 0))
		return(ft_cd(st, i, &(*env)));
	if ((ft_strncmp("env\0", (st + i), 4) == 0) || \
		(ft_strncmp("env ", (st + i), 4) == 0) || \
		(ft_strncmp("\"env\"", (st + i), 6) == 0) || \
		(ft_strncmp("\"env\" ", (st + i), 6) == 0))
		return(ft_env(&(*env)));
	if ((ft_strncmp("export\0", (st + i), 7) == 0) || \
		(ft_strncmp("export ", (st + i), 7) == 0) || \
		(ft_strncmp("\"export\"", (st + i), 9) == 0) || \
		(ft_strncmp("\"export\" ", (st + i), 9) == 0))
		return(ft_export(&(*env), st));
	return (3);
}
