/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_run_multiargs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:59:47 by corellan          #+#    #+#             */
/*   Updated: 2023/04/06 15:41:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_run_m_comman_aux(char **cmd, t_env *env, char *path, pid_t *pid)
{
	handle_shortcuts2();
	(*pid) = fork();
	if ((*pid) == -1)
	{
		perror("minishell");
		ft_free_split(cmd);
		return (3);
	}
	if ((*pid) == 0)
	{
		ft_child(path, cmd, &(*env));
		exit (EXIT_SUCCESS);
	}
	free(path);
	ft_free_split(cmd);
	return (3);
}

static int	run_mult_com(char **cmd, t_env *env, pid_t *pid)
{
	char	*path;
	int		flag;

	path = ft_find_path(cmd, &(*env), &flag);
	if (path == NULL)
		return (ft_print_error_command(cmd, &(*env), flag));
	return (ft_run_m_comman_aux(cmd, &(*env), path, &(*pid)));
}

static int	ft_handle_spe_cases(int *ret, t_env *env, t_m_arg *arg)
{
	arg->pid[arg->wait] = -1;
	arg->pid[(arg->wait) + 1] = 0;
	(arg->wait) += 1;
	if (arg->lex_size == arg->n_redir && arg->i == 0)
	{
		if (ft_strncmp("exit\0", (env->arr[0]), 5) == 0)
			return (ft_exit_check_m2(env->arr, &(*ret), &(*env)));
		if ((ft_strncmp("export\0", (env->arr[0]), 7) == 0))
			return (ft_export(&(*env), env->arr));
		if ((ft_strncmp("unset\0", (env->arr[0]), 6) == 0))
			return (ft_unset(&(*env), env->arr));
		if ((ft_strncmp("cd\0", (env->arr[0]), 3) == 0))
			return (ft_cd(env->arr, &(*env)));
	}
	return (-1);
}

static int	ft_proc_and_check_mul(char *ar, int *ret, t_env *env, t_m_arg *arg)
{
	env->arr = ft_custom_split(ar);
	env->arr = ft_process_arg(env->arr, ar);
	if (env->arr[0] != NULL)
	{
		if (ft_handle_spe_cases(&(*ret), &(*env), &(*arg)) != -1)
			return (3);
		if (ft_strncmp("exit\0", (env->arr[0]), 5) == 0)
			return (ft_exit_check_m1(env->arr, &(*ret), &(*env)));
		if (ft_strncmp("echo\0", (env->arr[0]), 5) == 0)
			return (ft_echo(env->arr, env));
		if ((ft_strncmp("pwd\0", (env->arr[0]), 4) == 0))
			return (ft_pwd(env));
		if ((ft_strncmp("cd\0", (env->arr[0]), 3) == 0))
			return (3);
		if ((ft_strncmp("env\0", (env->arr[0]), 4) == 0))
			return (ft_env(&(*env), env->arr));
		if ((ft_strncmp("export\0", (env->arr[0]), 7) == 0))
			return (ft_export_mult(&(*env), env->arr));
		if ((ft_strncmp("unset\0", (env->arr[0]), 6) == 0))
			return (ft_unset_mult(&(*env), env->arr));
		return (run_mult_com(env->arr, &(*env), &arg->pid[(arg->wait) - 1]));
	}
	ft_free_split(env->arr);
	return (3);
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
