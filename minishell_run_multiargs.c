/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_multiargs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:59:47 by corellan          #+#    #+#             */
/*   Updated: 2023/04/03 10:39:07 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_run_m_comman_aux(char **cmd, t_env *env, char *path, pid_t *pid)
{
	(*pid) = fork();
	if ((*pid) == -1)
	{
		perror("minishell");
		ft_free_split(cmd);
		return (3);
	}
	if ((*pid) == 0)
	{
		if (execve(path, cmd, env->env) < 0)
		{
			free(path);
			ft_free_split(cmd);
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	free(path);
	ft_free_split(cmd);
	env->exit_stts = 0;
	return (3);
}

static int ft_run_multiple_commands(char **cmd, t_env *env, pid_t *pid)
{
	char	*path;
	int		flag;

	path = ft_find_path(cmd, &(*env), &flag);
	if (path == NULL)
		return (ft_print_error_command(cmd, &(*env), flag));
	return (ft_run_m_comman_aux(cmd, &(*env), path, &(*pid)));
}

/*This function process the multi argument*/

static int	ft_proc_and_check_mul(char *ar, int *ret, t_env *env, t_m_arg *arg)
{
	char	**array;

	array = ft_custom_split(ar);
	array = ft_process_arg(array, ar);
	if (array[0] != NULL)
	{
		if (ft_strncmp("exit\0", (array[0]), 5) == 0)
			return (ft_exit_check(array, ar, &(*ret), &(*env)));
		if (ft_strncmp("echo\0", (array[0]), 5) == 0)
			return (ft_echo(array, env));
		if ((ft_strncmp("pwd\0", (array[0]), 4) == 0))
			return (ft_pwd(env));
		if ((ft_strncmp("cd\0", (array[0]), 3) == 0))
			return(ft_cd(array, &(*env)));
		if ((ft_strncmp("env\0", (array[0]), 4) == 0))
			return(ft_env(&(*env), array));
		if ((ft_strncmp("export\0", (array[0]), 7) == 0))
			return(ft_export(&(*env), array));
		if ((ft_strncmp("unset\0", (array[0]), 6) == 0))
			return(ft_unset(&(*env), array));
		return (ft_run_multiple_commands(array, &(*env), &arg->pid[arg->i]));
	}
	ft_free_split(array);
	return (3);
}

static int ft_process_reout(t_m_arg *arg)
{
	if (arg->lexe != NULL && arg->lexe->token == 5)
	{
		if (pipe(arg->fd) == -1)
		{
			perror("minishell");
			(arg->i) = arg->len;
			return (3);
		}
		arg->fdout_pipe = arg->fd[1];
		arg->fdin_pipe = arg->fd[0];
		arg->lexe = arg->lexe->next;
	}
	if (arg->flag_out == 1 || arg->flag_end == 1)
	{
		write(arg->fdout_pipe, "\0", 1);
		close(arg->fdout_pipe);
		dup2(arg->fdout, STDOUT_FILENO);
		close(arg->fdout);
	}
	else
	{
		dup2(arg->fdout_pipe, STDOUT_FILENO);
		close(arg->fdout_pipe);
	}
	return (0);
}

int	ft_iterate_mult_args(char **ar, int *re, t_env *env, t_m_arg *arg)
{
	ft_do_redirections(ar, &(*arg));
	if (ft_process_reout(&(*arg)) == 3)
		return (3);
	if (arg->flag_err == 0)
		ft_proc_and_check_mul(ar[arg->i], &(*re), &(*env), &(*arg));
	arg->idx = 0;
	while (arg->idx < arg->n_redir)
	{
		(arg->idx)++;
		(arg->i)++;
	}
	(arg->i)++;
	return (3);
}
