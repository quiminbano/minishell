/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:59:47 by corellan          #+#    #+#             */
/*   Updated: 2023/03/23 13:36:45 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_path(char **cmd, t_env *env)
{
	char	**array;
	char	*path;
	int		i;

	array = NULL;
	path = NULL;
	if (access(cmd[0], X_OK) == 0)
	{
		path = ft_strdup(cmd[0]);
		return (path);
	}
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

int ft_run_commands(char **cmd, t_env *env)
{
	pid_t	pid;
	int		fd[2];
	char	*path;

	path = ft_find_path(cmd, env);
	if (path == NULL)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		ft_free_split(cmd);
		return (3);
	}
	if (pipe(fd) == -1)
	{
		perror("minishell");
		ft_free_split(cmd);
		return (3);
	}
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
	return (3);
}