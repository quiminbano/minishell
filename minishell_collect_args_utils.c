/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:07:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/20 12:54:26 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Checks is the "word" after $ is a valid variable in env or not;
*/

char	*is_var_available(char *substr, t_env *env)
{
	int		i;
	char	*var;

	i = 0;
	var = NULL;
	while (env->env[i])
	{
		if ((var = ft_strnstr(env->env[i], substr, ft_strlen(substr))))
			return (var);
		i++;
	}
	return (NULL);
}