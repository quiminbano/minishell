/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:58:35 by corellan          #+#    #+#             */
/*   Updated: 2023/04/04 13:34:10 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function updates and replaces the existing enviromental variable we
want to change the value.*/

static void	ft_check_already_exist_aux(t_env *env, char **ar, int i, char *va)
{
	free(env->env[i]);
	env->env[i] = ft_strdup(ar[0]);
	if ((ar[1] != NULL) || ((ar[1] == NULL) && (va[ft_strlen(va) - 1] == '=')))
	{
		env->env[i] = ft_strjoin_free(env->env[i], "=");
		if (ar[1] != NULL)
			env->env[i] = ft_strjoin_free(env->env[i], ar[1]);
	}
	ft_free_split(ar);
}

/*This function checks if the variable we try to define with the export
command exists or not in the enviromental variables. if exists, processes
the new value defined for the existing enviromental variable and returns 1.
if it does not exist, returns 0.*/

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
	{
		ft_free_split(ar);
		return (0);
	}
	ft_check_already_exist_aux(&(*env), ar, i, variable);
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

	if (ft_check_plus(&(*env), variable) == 1)
		return ;
	if (ft_check_already_exist(&(*env), variable) == 1)
		return ;
	i = ft_array_len(env->env);
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

/*This function checks if the arguments to define new enviromental variables
are valid or not.*/

static void	ft_export_aux(char **array, int *i, t_env *env)
{
	if (((ft_wordcount_space(array[(*i)]) > 1) && \
		(ft_strchr(array[(*i)], '=') == NULL)) || ((array[(*i)][0] > 47) && \
		(array[(*i)][0] < 58)))
	{
		env->exit_stts = 1;
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	else if (ft_check_first_variable(array[(*i)]) == 1)
	{
		env->exit_stts = 1;
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, array[(*i)], ft_strlen(array[(*i)]));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		(*i)++;
		return ;
	}
	check_and_process_d_quotes(&(array[(*i)]));
	ft_add_variables(&(*env), array[(*i)]);
	(*i)++;
}

/*This function checks the arguments when the command export is called. 
First, the function checks how many arguments are in the 2D array with
the command parsed. if it is just one argument, the function calls the
function ft_sort_and_print_strings, that prints the enviroment variables
sorted by ASCII index. If there is more than one argument in the command
and and the second argument starts with the - character, the function
prints an error. if there is some futher stuff to be checked, the function
calls the ft_export_aux function.*/

int	ft_export(t_env *env, char **array)
{
	int	i;

	i = ft_array_len(array);
	env->exit_stts = 0;
	if (i == 1)
		ft_sort_and_print_strings(env->env);
	else
	{
		i = 1;
		if (ft_strlen(array[i]) > 1 && array[i][0] == '-')
		{
			env->exit_stts = 1;
			write(STDERR_FILENO, "minishell: export: Options are not ", 35);
			write(STDERR_FILENO, "available in this version of export\n", 36);
		}
		else
		{
			while (array[i] != NULL)
				ft_export_aux(array, &i, &(*env));
		}
	}
	if (array != NULL)
		ft_free_split(array);
	return (3);
}
