/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:01:20 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/13 14:59:43 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function checks if the command written after $ is a valid environment variable
	or not, if so, it will store the variable's value (ready to be printed) in env->var_value
*/
static int    is_cmd_valid(char *cmd, t_env *env)
{
    int     i;
    int     var_len;

    i = 0;
    var_len = ft_strlen(cmd);
    while (env->env[i])
    {
        if (ft_strnstr(env->env[i], cmd, ft_strlen(env->env[i])))
        {
            env->var_value = ft_strdup(env->env[i] + var_len + 1);
            return (1);
        }
        else
            i++;
    }
	env->var_value = ft_strdup("");
    return (0);
}

/*
	we get the command written after $, skip the $ sign and cut everything after the space after
	the command.Now we have the command which is supposed to equal the environment variable 
	name, like (OLDPWD, PWD...)
	After this we call is_cmd_valid
*/
static int         get_cmd(char *s, t_env *env)
{
    char    *dollar_pos;
    char    **cmd;

    if (s[0] == '$')
        dollar_pos = s;
    else
        dollar_pos = ft_strnstr(s, " $", ft_strlen(s)) + 1;
    dollar_pos++;
    cmd = ft_split(dollar_pos, ' ');
    if (is_cmd_valid(cmd[0], env))
	{
		ft_free_split(cmd);
		return (1);
	}
	else
	{
		ft_free_split(cmd);
		return (0);
	}
    
}

/*
	Checks if there a $ sign in the beginning, or after a space, 
	If so, we call get_cmd, to get the command written after $
	If we have a $ sign AND a valid command, the function will return 1.
*/

int check_dollar(char *s, t_env *env)
{
    if ((ft_strnstr(s, " $", ft_strlen(s)) || s[0] == '$') && get_cmd(s, env))
		return (1);
	return (0);
}