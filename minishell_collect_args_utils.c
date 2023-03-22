/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:07:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/21 15:51:05 by hel-hosr         ###   ########.fr       */
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
	char	*add_equal;

	add_equal = ft_strjoin(substr, "=");
	i = 0;
	var = NULL;
	while (env->env[i])
	{
		if ((var = ft_strnstr(env->env[i], add_equal, ft_strlen(add_equal))))
		{
			free(add_equal);
			return (var);
		}
		i++;
	}
	free(add_equal);
	return (NULL);
}

void	handle_exlamation(t_env *env, char *substr)
{
	char	*num;
	char	*str;

	str = NULL;
	num = NULL;
	
	num = ft_itoa(env->exit_stts);
	env->new_str = ft_strjoin_free(env->new_str, num);
	free(num);
	if (substr[1] != '\0')
	{
		str = ft_strdup(substr + 1);
		env->new_str = ft_strjoin_free(env->new_str, str);
		free(str);
	}
}