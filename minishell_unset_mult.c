/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset_mult.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:00:13 by corellan          #+#    #+#             */
/*   Updated: 2023/04/03 17:55:29 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function checks if the arguments passed to the ft_unset_aux function
are valid or not.*/

static int	ft_check_unset_variable(char *variable)
{
	int		i;

	i = 0;
	if (ft_strlen(variable) == 0)
		return (1);
	while ((variable[i] > 47 && variable[i] < 58) || \
		(variable[i] > 64 && variable[i] < 91) || \
		(variable[i] > 96 && variable[i] < 123) || (variable[i] == 95))
		i++;
	if (i < (int)ft_strlen(variable))
		return (1);
	return (0);
}

/*This function is similar to ft_export_aux. So, it check if the arguments
we pass are valid.*/

static void	ft_unset_m_aux(char **array, int *i, t_env *env)
{
	if ((ft_wordcount_space(array[(*i)]) > 1) || ((array[(*i)][0] > 47) && \
		(array[(*i)][0] < 58)))
	{
		env->exit_stts = 1;
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	else if (ft_check_unset_variable(array[(*i)]) == 1)
	{
		env->exit_stts = 1;
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	(*i)++;
}

/*This function is similar to ft_unset. The difference is that when we call
unset without any variable, the programm does not do anything.*/

int	ft_unset_mult(t_env *env, char **array)
{
	int	i;

	env->exit_stts = 0;
	i = ft_array_len(array);
	if (i == 1)
	{
		ft_free_split(array);
		return (3);
	}
	i = 1;
	if (ft_strlen(array[i]) > 1 && array[i][0] == '-')
	{
		env->exit_stts = 1;
		write(STDERR_FILENO, "minishell: unset: Options are not ", 34);
		write(STDERR_FILENO, "available in this version of unset\n", 35);
	}
	else
	{
		while (array[i] != NULL)
			ft_unset_m_aux(array, &i, &(*env));
	}
	if (array != NULL)
		ft_free_split(array);
	return (3);
}
