/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_mult.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:58:35 by corellan          #+#    #+#             */
/*   Updated: 2023/04/03 13:15:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function checks if the arguments to define new enviromental variables
are valid or not.*/

static void	ft_export_m_aux(char **array, int *i, t_env *env)
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

int	ft_export_mult(t_env *env, char **array)
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
				ft_export_m_aux(array, &i, &(*env));
		}
	}
	if (array != NULL)
		ft_free_split(array);
	return (3);
}
