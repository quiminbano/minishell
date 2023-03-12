/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:58:35 by corellan          #+#    #+#             */
/*   Updated: 2023/03/12 15:23:13 by corellan         ###   ########.fr       */
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
