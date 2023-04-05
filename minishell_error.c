/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:59:58 by corellan          #+#    #+#             */
/*   Updated: 2023/04/05 17:06:06 by hel-hosr         ###   ########.fr       */
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

static int	more_than_two(char *st)
{
	int	i;

	i = 0;
	while (st[i])
	{
		if (st[i] == '>' && st[i + 1] == '>' && st[i + 2]
			== '>' && st[i + 3] != '>')
			return (3);
		else if (st[i] == '>' && st[i + 1] == '>' && st[i + 2]
			== '>' && st[i + 3] == '>')
			return (4);
		i++;
	}
	return (0);
}

static int	check_errors_helper(char *st, int i, int inside, t_env *env)
{
	while (st[i])
	{
		inside = is_inside(st[i], env);
		if (st[i] == '\\' && st[i + 1])
			i++;
		else if (more_than_two(st))
			return (ft_error_more_than_two(more_than_two(st)));
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
		else if ((st[i] == '|' && !st[i + 1]) || (st[i] == '\\' && !st[i + 1]))
			return (ft_error_unsupported());
		i++;
	}
	return (0);
}

int	catch_errors(char *st, t_env *env)
{	
	int	i;
	int	inside;

	i = 0;
	inside = 0;
	env->is_inside_q = 0;
	env->is_inside_dq = 0;
	return (check_errors_helper(st, i, inside, env));
}
