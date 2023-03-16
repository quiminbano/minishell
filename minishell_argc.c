/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:35:02 by corellan          #+#    #+#             */
/*   Updated: 2023/03/16 13:25:29 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_work_in_arg_aux(char **array, int pos, int *j, char **str)
{
	int	flag;

	flag = 0;
	while ((*j) < pos)
	{
		if (flag == 0)
		{
			(*str) = ft_strdup(array[(*j)]);
			flag = 1;
		}
		else
			(*str) = ft_strjoin_free((*str), array[(*j)]);
		(*j)++;
	}
}

static char	*ft_work_in_arg(char **array, int pos, int *j)
{
	int			flag;
	char		*str;

	flag = 0;
	if ((pos - (*j)) == 1)
	{
		str = ft_strdup(array[(*j)]);
		(*j) += 1;
		return (str);
	}
	else if (pos == (*j))
	{
		str = ft_strdup("");
		return (str);
	}
	else
		ft_work_in_arg_aux(array, pos, &(*j), &str);
	return (str);
}

static char	**ft_process_arg_aux(char **ar, char **tem, int len, t_echo **arg)
{
	t_echo	*args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = (*arg);
	while (i < len)
	{
		tem[i] = ft_work_in_arg(ar, args->pos, &j);
		if (args->next != NULL)
			args = args->next;
		i++;
	}
	args = (*arg);
	if (args != NULL)
		ft_free_list_echo(&args);
	ft_free_split(ar);
	return (tem);
}

char	**ft_process_arg(char **array, char *str)
{
	t_echo	*args;
	char	**temp;
	int		len;

	args = NULL;
	ft_wordcount_echo(str, &args);
	len = ft_listsize_echo(&args);
	temp = (char **)malloc(sizeof(char *) * (len + 1));
	if (temp == NULL)
		return (NULL);
	temp[len] = NULL;
	return (ft_process_arg_aux(array, temp, len, &args));
}

/*This function check many thins. First it checks that the string is not NULL.
If it is not NULL, the function add_history is called to cast the history of
the commands written. It also check if we press ctrl + D in the terminal to
indicate the end of file (EOF). This is not handled properly yet. Finally, 
the function check the differents ways that the command exit needs to be written
to be valid. */

int	ft_line_checker(char *st, int *ret, t_env *env)
{
	char	**array;

	if (st != NULL && ft_strlen(s) > 0)
	{	
		add_history(st);
		collect_args(st, env);
		st = ft_strdup(env->new_str);
		free(env->new_str);
	}
	if (st == (void *)0)
		return(handle_ctrlD(st));
	array = ft_custom_split(st);
	array = ft_process_arg(array, st);
	if (array[0] != NULL)
	{
		if (ft_strncmp("exit\0", (array[0]), 5) == 0)
		{
			if (ft_check_symbols(st) == 0)
				return (ft_exit_check(array, st, &(*ret)));
			else
				return (3);
		}
		if (ft_strncmp("echo\0", (array[0]), 5) == 0)
			return (ft_echo(array));
		if ((ft_strncmp("pwd\0", (array[0]), 4) == 0))
			return (ft_pwd());
		if ((ft_strncmp("cd\0", (array[0]), 3) == 0))
			return(ft_cd(array, &(*env)));
		if ((ft_strncmp("env\0", (array[0]), 4) == 0))
			return(ft_env(&(*env)));
		if ((ft_strncmp("export\0", (array[0]), 7) == 0))
			return(ft_export(&(*env), array));
	}
	return (3);
}
