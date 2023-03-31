/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:59:58 by corellan          #+#    #+#             */
/*   Updated: 2023/03/31 13:57:52 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_inside(char c, t_env *env)
{
	if (c == '\'' && !env->is_inside_q)
		env->is_inside_q = 1;
	else if (c == '\'' && env->is_inside_q)
		env->is_inside_q = 0;
	if (c == '"' && !env->is_inside_dq)
		env->is_inside_dq = 1;
	else if (c == '"' && env->is_inside_dq)
		env->is_inside_dq = 0;
	if (env->is_inside_q == 1 || env->is_inside_dq == 1)
		return (1);
	else
		return (0);
}

static int	first_or_both(char *st)
{
	if (st[0] == '|' && st[1] != '|')
		return (1);
	else if (st[0] == '|' && st[1] == '|')
		return (2);
	return (0);
}

/*
	catch and throw error when it finds:
	- | and || in the beginning of the line
	- < or > at the end of line
	- && and <<<
	- \< \! --- \<\<
	- >< ><< ><<<
*/
int	catch_errors(char *st, t_env *env)
{	
	int	i;
	int	inside;

	i = 0;
	inside = 0;
	env->is_inside_q = 0;
	env->is_inside_dq = 0;
	while (st[i])
	{
		inside = is_inside(st[i], env);
		if (st[i] == '\\')
			i++;
		else if (first_or_both(st) != 0)
			return (ft_error_pipe(first_or_both(st)));
		else if (((st[i] == '<' && st[i + 1] == '<' && st[i + 2] == '<')
				&& (!inside)) || ((st[i] == '&' && st[i + 1] == '&')
				&& (!inside)))
			return (ft_error_unsupported());
		else if ((st[i] == '>' && st[i + 1] == '<') && (!inside))
			return (ft_error_redir(1, st, i));
		else if ((st[ft_strlen(st) - 1] == '<' || st[ft_strlen(st) - 1] == '>'))
			return (ft_error_redir(2, st, i));
		i++;
	}
	return (0);
}
