/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:58:35 by corellan          #+#    #+#             */
/*   Updated: 2023/03/15 14:08:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function copies back the information stored in the temp 2D array into the
env->env 2D array. This new enviromental 2D has now the new enviromental variable
defined.*/

static void	ft_add_variables_copy_back(t_env *env, char **array, int i)
{
	ft_free_split(env->env);
	env->env = (char **)malloc(sizeof(char *) * (i + 2));
	if (env->env == NULL)
		return ;
	env->env[i + 1] = NULL;
	i = 0;
	while (array[i] != NULL)
	{
		env->env[i] = ft_strdup(array[i]);
		i++;
	}
	ft_free_split(array);
}

static int	ft_check_already_exist(t_env *env, char *variable)
{
	char	**ar;
	int		i;

	i = 0;
	ar = ft_split(variable, '=');
	while (env->env[i] != NULL)
	{
		if ((ft_strncmp(env->env[i], ar[0], ft_strlen(ar[0])) == 0) && \
			((env->env[i][ft_strlen(ar[0])] == '\0') || \
			(env->env[i][ft_strlen(ar[0])] == '=')))
				break ;
		i++;
	}
	if (env->env[i] == NULL)
		return (0);
	free(env->env[i]);
	env->env[i] = ft_strdup(ar[0]);
	if (ar[1] != NULL)
	{
		env->env[i] = ft_strjoin_free(env->env[i], "=");
		env->env[i] = ft_strjoin_free(env->env[i], ar[1]);
	}
	ft_free_split(ar);
	return (1);
}

/*This function adds an enviromental variable to the env->env 2D array.
This function is really useful to add enviromental variables through
our implementation of the export command (not ready yet). This function
copies the env->env into a temporary 2D array (**array). This temp 2D array
is malloced with one extra space than the original env->env 2D array.
The reason of that is because, we need an extra space to store the new
enviromental variable.*/

void	ft_add_variables(t_env *env, char *variable)
{
	char	**array;
	int		i;

	i = 0;
	if (ft_check_already_exist(&(*env), variable) == 1)
		return ;
	while (env->env[i] != NULL)
		i++;
	array = (char **)malloc(sizeof(char *) * (i + 2));
	if (array == NULL)
		return ;
	array[i + 1] = NULL;
	i = 0;
	while (env->env[i] != NULL)
	{
		array[i] = ft_strdup(env->env[i]);
		i++;
	}
	array[i] = ft_strdup(variable);
	ft_add_variables_copy_back(&(*env), array, i);
}

static void	ft_export_aux(char **array, int *i, t_env *env)
{
	if (((ft_wordcount_argc(array[(*i)]) > 1) && \
		(ft_strchr(array[(*i)], '=') == NULL)) || ((array[(*i)][0] > 47) && \
		(array[(*i)][0] < 58)))
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	else if (ft_check_first_variable(array[(*i)]) == 1)
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	ft_add_variables(&(*env), array[(*i)]);
	(*i)++;
}

int	ft_export(t_env *env, char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i == 1)
		ft_sort_and_print_strings(env->env);
	else
	{
		i = 1;
		while (array[i] != NULL)
			ft_export_aux(array, &i, &(*env));
	}
	if (array != NULL)
		ft_free_split(array);
	return (3);
}
