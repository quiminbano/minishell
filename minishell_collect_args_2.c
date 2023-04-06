/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:53:38 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/06 15:42:22 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_or_out_2(char *st, int i, t_env *env)
{
	if (st[i] == '"' && !env->is_inside_2)
		env->is_inside_2 = 1;
	else if (st[i] == '"' && env->is_inside_2)
		env->is_inside_2 = 0;
	return (1);
}

int	single_inside_double(char *st, int i)
{
	while (st[i])
	{
		if (st[i] == '\'')
			return (1);
		else if (st[i] == '"')
			return (0);
		i++;
	}
	return (0);
}
