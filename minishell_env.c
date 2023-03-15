/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:14:47 by corellan          #+#    #+#             */
/*   Updated: 2023/03/15 13:59:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function increase the shell level (SHLVL) in one unit.*/

static void	ft_update_shlvl(int i, t_env *env)
{
	char	**array;
	char	*number;
	int		level;

	array = ft_split(env->env[i], '=');
	if (array == NULL)
		return ;
	level = ft_atoi(array[1]);
	number = ft_itoa(level + 1);
	free(env->env[i]);
	array[0] = ft_strjoin_free(array[0], "=");
	env->env[i] = ft_strjoin(array[0], number);
	free(number);
	ft_free_split(array);
}

/*This function defines OLDPWD empty if does not exist in the original envp
2D array. This function also modified the shell level in one unit.*/

static void	ft_copy_env_aux(t_env *env, int i)
{
	if (env->flag == 0)
	{
		ft_add_variables(&(*env), "OLDPWD");
		env->flag = 1;
	}
	while (ft_strncmp("SHLVL=", env->env[i], 6) != 0)
		i++;
	ft_update_shlvl(i, &(*env));
}

/*This function copies the original envp 2D, that is coming from zsh or bash
to our program. We also modified the OLDPWD, if exists, to be empty when we
start the minishell.*/

void	ft_copy_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	env->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (env->env == NULL)
		exit(1);
	env->env[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("OLDPWD=", envp[i], 7) == 0)
		{
			env->env[i] = ft_strdup("OLDPWD");
			env->flag = 1;
			printf("%d\n", env->flag);
		}
		else
			env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	i = 0;
	ft_copy_env_aux(&(*env), i);
}

/*This function prints the enviroment variables that have a defined value in
the env 2D array. We can know if an eviromental variable has a value if the
equal character (=) is present in the string. Also, we need to print the
route /usr/bin/env when */

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i] != NULL)
	{
		if(ft_strchr(env->env[i], '=') != NULL)
		{
			if(ft_strncmp("_=", env->env[i], 2) == 0)
				printf("_=/usr/bin/env\n");
			else
				printf("%s\n", env->env[i]);
		}
		i++;
	}
	return (3);
}
