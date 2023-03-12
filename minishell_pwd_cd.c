/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:10:18 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/12 15:03:23 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function updates the oldpwd enviroment variable, depending if oldpwd was
written before or not. We identified this with env->flag.*/

static void	ft_env_update_oldpwd(t_env *env, char **array, int i)
{
	if (env->flag == 2)
	{
		while (ft_strncmp("OLDPWD=", env->env[i], 7) != 0)
			i++;
		array = ft_split(env->env[i], '=');
		if (array == NULL)
			return ;
		free(env->env[i]);
		array[0] = ft_strjoin_free(array[0], "=");
		env->env[i] = ft_strjoin(array[0], env->oldpwd);
		ft_free_split(array);
	}
	else if (env->flag == 1)
	{
		while (ft_strncmp("OLDPWD", env->env[i], 6) != 0)
			i++;
		env->env[i] = ft_strjoin_free(env->env[i], "=");
		env->env[i] = ft_strjoin_free(env->env[i], env->oldpwd);
		env->flag = 2;
	}
}

/*This function overwrite the information of the variables PWD and OLDPWD in
the enviromental variables, everytime that the command cd is called and changes
directory successfully. */

static void	ft_env_update(t_env *env)
{
	char	**array;
	int		i;

	i = 0;
	while (ft_strncmp("PWD=", env->env[i], 4) != 0)
		i++;
	array = ft_split(env->env[i], '=');
	if (array == NULL)
		return ;
	free(env->env[i]);
	array[0] = ft_strjoin_free(array[0], "=");
	env->env[i] = ft_strjoin(array[0], env->newpwd);
	ft_free_split(array);
	i = 0;
	ft_env_update_oldpwd(&(*env), array, i);

}

/*	print working directory path
	print error if fail.
*/
int	ft_pwd(void)
{
	char	path[BUFFER];

	if (getcwd(path, sizeof(path)))
		printf("%s\n", path);
	else
		perror("minishell");
	return (3);
}

/*
	str = everything typed after "cd"
	path = it takes str, and if a space is found, everything after it is cut, as in the original cd
	if we have a space after the path and some other text after the space, cd would still work, taking 
	in consideration the path before the space.
	e.g in: cd ./desktop/application/ garbage text
	"garbage text" will be ignored and the path "./desktop/application/" will apply.
	UPDATE
	ft_cd now tracks the information about the directory we are now and the
	directory we want to access. So, we can print the variable OLDPWD enerytime
	we call the command env. Another change I did is, now, when we fail to
	change directory, we print the message in the STDERR instead of the STDOUT.
*/
int	ft_cd(char *s, int i, t_env *env)
{
	char	*str;
	char	**path;

	str = ft_strdup(s + i + 3);
	path = ft_split(str, ' ');
	getcwd(env->oldpwd, sizeof(env->oldpwd));
	if (chdir(path[0]) == 0)
	{
		getcwd(env->newpwd, sizeof(env->newpwd));
		ft_env_update(&(*env));
	}
	else
	{
		write(STDERR_FILENO, "minishell: cd: ", 15);
		write(STDERR_FILENO, path[0], ft_strlen(path[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
	}
	free(str);
	ft_free_split(path);
	return (3);
}
