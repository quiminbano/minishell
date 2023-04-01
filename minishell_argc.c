/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/04/01 16:17:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function process the line when we put just one single command, without
any special token (|, <, >, <<, >>)*/

static int	ft_process_single_cmd(char *st, int *ret, t_env *env)
{
	char	**array;

	collect_args(st, &(*env));
	array = ft_custom_split(env->new_str);
	array = ft_process_arg(array, env->new_str);
	if (array[0] != NULL)
	{
		if (ft_strncmp("exit\0", (array[0]), 5) == 0)
			return (ft_exit_check(array, st, &(*ret), &(*env)));
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
		return (ft_run_single_command(array, &(*env)));
	}
	ft_free_split(array);
	return (3);
}

static void	ft_w_for_proc_free_and_close(char **ar, t_m_arg *arg, t_lexer **be)
{
	arg->i = 0;
	close(arg->fdin_pipe);
	close(arg->fdout_pipe);
	while (arg->pid[arg->i] != 0)
		waitpid(arg->pid[((arg->i)++)], NULL, 0);
	ft_free_split(ar);
	arg->lexe = (*be);
	ft_free_list_lexer(&(arg->lexe));
	dup2(arg->tmpout, STDOUT_FILENO);
	close(arg->tmpout);
	dup2(arg->tmpin, STDIN_FILENO);
	close(arg->tmpin);
}

/*This function prepares the arguments to be processed to run an multiargument
instruccion.*/

static int	ft_process_multi_cmd(char **ar, int *ret, t_env *env, t_lexer **le)
{
	t_m_arg	arg;

	arg.lexe = (*le);
	arg.lex_f = 0;
	if (arg.lexe->token == 0)
		arg.lex_f = 1;
	if (arg.lexe->token == 0)
		arg.lexe = arg.lexe->next;
	arg.i = 0;
	arg.tmpin = dup(STDIN_FILENO);
	arg.tmpout = dup(STDOUT_FILENO);
	if (arg.lexe != NULL && ((arg.lexe->token == 2) || \
		(arg.lexe->token == 4) || (arg.lexe->token == 5)))
		arg.fdin = dup(arg.tmpin);
	arg.fdin_pipe = dup(arg.tmpin);
	arg.len = ft_array_len(ar);
	arg.pid[arg.len] = 0;
	while (ar[arg.i] != NULL)
		ft_iterate_mult_args(ar, &(*ret), &(*env), &arg);
	ft_w_for_proc_free_and_close(ar, &arg, &(*le));
	return (3);
}

static int	ft_replace_dol_multi(char **ar, int *ret, t_env *env, t_lexer **le)
{
	int	i;

	i = 0;
	while (ar[i] != NULL)
	{
		if (i >= 1)
			env->new_str = ft_strdup("");
		collect_args(ar[i], &(*env));
		free(ar[i]);
		ar[i] = ft_strdup(env->new_str);
		i++;
		if (ar[i] != NULL)
			free(env->new_str);
	}
	return (ft_process_multi_cmd(ar, &(*ret), &(*env), &(*le)));
}

/*This function check many thins. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid.*/

int	ft_line_checker(char *st, int *ret, t_env *env)
{
	t_lexer	*lex;
	char	**args;

	lex = NULL;
	args = NULL;
	env->new_str = ft_strdup("");
	if (st != NULL && ft_strlen(st) > 0)
		add_history(st);
	if (st == (void *)0)
		return(handle_ctrlD(st, env));
	if (st[0] == '|')
		return (ft_error_pipe(st));
	ft_tokens_recognition(st, &lex);
	if (lex != NULL && ft_listsize_lexer(&lex) == 1 && lex->token == 0)
	{
		ft_free_list_lexer(&lex);
		return (ft_process_single_cmd(st, &(*ret), &(*env)));
	}
	else if (lex != NULL)
	{
		args = ft_split_lexer(st);
		args = ft_process_lexer(args, st);
		return (ft_replace_dol_multi(args, &(*ret), &(*env), &lex));
	}
	return (3);
}
