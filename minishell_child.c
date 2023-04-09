/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:55:01 by corellan          #+#    #+#             */
/*   Updated: 2023/04/09 07:57:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_child_aux(char **cmd, t_env *env, int flag, t_m_arg *arg)
{
	if ((ft_strncmp("env\0", (cmd[0]), 4) == 0))
	{
		ft_env(&(*env), cmd);
		flag = 1;
	}
	else if ((ft_strncmp("export\0", (cmd[0]), 7) == 0))
	{
		ft_export_mult(&(*env), cmd);
		flag = 1;
	}
	else if ((ft_strncmp("unset\0", (cmd[0]), 6) == 0))
	{
		ft_unset_mult(&(*env), cmd);
		flag = 1;
	}
	if (flag == 1)
	{
		ft_free_list_lexer(&(arg->begin));
		free(env->new_str);
		free(*(env->str));
		free(*(arg->path));
		exit (env->exit_stts);
	}
	return (0);
}

static int	process_child(char **cmd, t_env *env, t_m_arg *arg)
{
	int	flag;

	flag = 0;
	if (ft_strncmp("exit\0", (cmd[0]), 5) == 0)
	{
		ft_exit_check_m1(cmd, &(env->ret), &(*env));
		flag = 1;
	}
	else if (ft_strncmp("echo\0", (cmd[0]), 5) == 0)
	{
		ft_echo(env->arr, env);
		flag = 1;
	}
	else if ((ft_strncmp("pwd\0", (cmd[0]), 4) == 0))
	{
		ft_pwd(env);
		flag = 1;
	}
	else if ((ft_strncmp("cd\0", (cmd[0]), 3) == 0))
	{
		ft_cd(env->arr, &(*env));
		flag = 1;
	}
	return (process_child_aux(cmd, &(*env), flag, &(*arg)));
}

void	ft_child(char *path, char **cmd, t_env *env, t_m_arg *arg)
{
	arg->path = &path;
	ft_process_rein(&(*arg));
	ft_process_reout(&(*arg));
	if (process_child(cmd, &(*env), &(*arg)) != 0)
		exit (EXIT_SUCCESS);
	if (execve(path, cmd, env->env) < 0)
	{
		free(path);
		ft_free_split(cmd);
		write(STDERR_FILENO, "minishell: : command not found\n", 31);
		exit (127);
	}
}

void	ft_child_s(char *path, char **cmd, t_env *env)
{
	if (execve(path, cmd, env->env) < 0)
	{
		free(path);
		ft_free_split(cmd);
		write(STDERR_FILENO, "minishell: : command not found\n", 31);
		exit (127);
	}
}
