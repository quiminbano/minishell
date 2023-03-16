/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:42:40 by corellan          #+#    #+#             */
/*   Updated: 2023/03/16 17:28:44 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_aux(char **array, int *i, t_env *env)
{
	if (((ft_wordcount_argc(array[(*i)]) > 1) && \
		(ft_strchr(array[(*i)], '=') == NULL)) || ((array[(*i)][0] > 47) && \
		(array[(*i)][0] < 58)))
	{
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	else if (ft_check_first_variable(array[(*i)]) == 1)
	{
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	ft_remove_variables(&(*env), array[(*i)]);
	(*i)++;
}

int	ft_unset(t_env *env, char **array)
{
	int	i;

	i = ft_array_len(array);
	if (i == 1)
		return (3);
	i = 1;
	if (ft_strlen(array[i]) > 1 && array[i][0] == '-')
	{
		write(STDERR_FILENO, "minishell: unset: Options are not ", 34);
		write(STDERR_FILENO, "available in this version of unset\n", 35);
	}
	else
	{
		while (array[i] != NULL)
			ft_unset_aux(array, &i, &(*env));
	}
	if (array != NULL)
		ft_free_split(array);
	return (3);
}