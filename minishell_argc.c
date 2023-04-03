/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/30 15:05:36 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	ft_process_multi_cmd(char *st, int *ret, t_env *env, t_lexer **lex)
{
	t_multarg	arg;

	arg.args = ft_split_lexer(st);
	arg.args = ft_process_lexer(arg.args, st);
	arg.i = ft_array_len(arg.args);
	arg.flag = 0;
	arg.array = (char ***)malloc(sizeof(char **) * (arg.i + 1));
	if (arg.array == NULL)
		return (3);
	arg.i = 0;
	while (arg.args[arg.i] != NULL)
	{
		if (arg.flag == 1)
			env->new_str = ft_strdup("");
		collect_args(arg.args[arg.i], &(*env));
		arg.array[arg.i] = ft_custom_split(env->new_str);
		arg.array[arg.i] = ft_process_arg(arg.array, env->new_str);
		(arg.i)++;
		if (arg.args[arg.i] != NULL)
			free(env->new_str);
		arg.flag = 1;
	}
	ft_free_list_lexer(&(*lex));
	return (3);
}*/

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

/*This function check many things. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid. */

int	ft_line_checker(char *st, int *ret, t_env *env)
{
	t_lexer	*lex;

	lex = NULL;
	env->new_str = ft_strdup("");
	if (st != NULL && ft_strlen(st) > 0)
		add_history(st);
	if (st == (void *)0)
		return(handle_ctrlD(st, env));
	if (catch_errors(st, env) == 1)
		return (3);
	ft_tokens_recognition(st, &lex);
	if (lex != NULL && ft_listsize_lexer(&lex) == 1 && lex->token == 0)
	{
		ft_free_list_lexer(&lex);
		return (ft_process_single_cmd(st, &(*ret), &(*env)));
	}
	/*else
		return (ft_process_multi_cmd(st, &(*ret), &(*env), &lex));*/
	return (3);
}
