/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:42:40 by corellan          #+#    #+#             */
/*   Updated: 2023/03/17 17:15:04 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function copies back the information that it is in the temp 2D-array 
without the removed enviroment variable.*/

static void	ft_copy_back_after_unset(t_env *env, char **array, int i)
{
	ft_free_split(env->env);
	env->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (env->env == NULL)
		return ;
	env->env[i] = NULL;
	i = 0;
	while (array[i] != NULL)
	{
		env->env[i] = ft_strdup(array[i]);
		i++;
	}
	ft_free_split(array);
}

/*This function removes an enviromental variable to the env->env 2D array.
This function copies the env->env into a temporary 2D array (**array). 
This temp 2D array is malloced with one less space than the original env->env 
2D array. The reason of that is because, we need to skip of copying the variable
we want to remove.*/

void	ft_remove_variables(t_env *env, char *variable)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	i = ft_array_len(env->env);
	j = 0;
	if (ft_find_word_array(env->env, variable) == i)
		return ;
	k = ft_find_word_array(env->env, variable);
	array = (char **)malloc(sizeof(char *) * (i));
	if (array == NULL)
		return ;
	array[i - 1] = NULL;
	i = 0;
	while (env->env[j] != NULL)
	{
		array[i] = ft_strdup(env->env[j]);
		j++;
		i++;
		if (j == k)
			j++;
	}
	ft_copy_back_after_unset(&(*env), array, i);
}

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

static void	ft_unset_aux(char **array, int *i, t_env *env)
{
	if ((ft_wordcount_argc(array[(*i)]) > 1) || ((array[(*i)][0] > 47) && \
		(array[(*i)][0] < 58)))
	{
		write(STDERR_FILENO, "minishell: unset: `", 19);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	else if (ft_check_unset_variable(array[(*i)]) == 1)
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

/*This function is similar to ft_export. The difference is that when we call
unset without any variable, the programm does not do anything.*/

int	ft_unset(t_env *env, char **array)
{
	int	i;

	i = ft_array_len(array);
	if (i == 1)
	{
		ft_free_split(array);
		return (3);
	}
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