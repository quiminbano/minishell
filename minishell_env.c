/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:14:47 by corellan          #+#    #+#             */
/*   Updated: 2023/03/11 17:44:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	i = 0;
	while (ft_strncmp("SHLVL=", env->env[i], 6) != 0)
		i++;
	ft_update_shlvl(i, &(*env));
}

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (3);
}
