/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_singleargs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:59:47 by corellan          #+#    #+#             */
/*   Updated: 2023/03/27 11:11:23 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_path_aux(char **cmd, t_env *env, int i, char **array)
{
	char	*path;

	path = NULL;	
	i = ft_find_word_array(env->env, "PATH=");
	if (i < ft_array_len(env->env))
		array = ft_split(env->env[i] + 5, ':');
	i = 0;
	while (array[i] != NULL)
	{
		path = ft_strjoin(array[i], "/");
		path = ft_strjoin_free(path, cmd[0]);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (i == ft_array_len(array))
		path = NULL;
	ft_free_split(array);
	return (path);
}

static char	*ft_find_path(char **cmd, t_env *env)
{
	char	*path;
	char	**array;
	int		i;

	path = NULL;
	array = NULL;
	i = 0;
	if (access(cmd[0], X_OK) == 0)
	{
		path = ft_strdup(cmd[0]);
		return (path);
	}
	return (ft_find_path_aux(cmd, &(*env), i, &(*array)));
}

static int	ft_run_single_command_aux(char **cmd, t_env *env, char *path, pid_t pid)
{
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		ft_free_split(cmd);
		return (3);
	}
	if (pid == 0)
	{
		if (execve(path, cmd, env->env) < 0)
		{
			free(path);
			ft_free_split(cmd);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, NULL, 0);
	free(path);
	ft_free_split(cmd);
	env->exit_stts = 0;
	return (3);
}

int ft_run_single_command(char **cmd, t_env *env)
{
	pid_t	pid;
	char	*path;

	pid = 1;
	path = ft_find_path(cmd, env);
	if (path == NULL)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		ft_free_split(cmd);
		env->exit_stts = 127;
		return (3);
	}
	return (ft_run_single_command_aux(cmd, &(*env), path, pid));
}