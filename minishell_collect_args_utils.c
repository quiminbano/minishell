/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:07:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/23 16:28:55 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	this function takes the string or var name that we need to check its validity,e.g "USER"
	and adds the "=" sign to it, and then comapares it to all the env variables stored in env->env,
	if the variable is found, the function returns a pointer to it.
	when this function is called from handle_vars(), if it finds a variable its gonna return the whole line,e.g:
	USER=hel-hosr. Thats why after calling this function, we only strjoin everything after the "=" sign from the 
	returned pointer, and not from the beginning of the str. (we move the pointer "variable_name_length times + 1")
*/
char	*is_var_available(char *substr, t_env *env)
{
	int		i;
	char	*var;
	char	*add_equal;

	var = NULL;
	add_equal = ft_strjoin(substr, "=");
	i = 0;
	while (env->env[i])
	{
		var = ft_strnstr(env->env[i], add_equal, ft_strlen(add_equal));
		if (var)
		{
			free(add_equal);
			return (var);
		}
		i++;
	}
	free(add_equal);
	return (NULL);
}
/*
	this behave the same way as strjoin, but it joins 1 character instead of a string to s1
	this one is handling free(s1)
*/
char	*ft_strjoin_c(char *s1, char const c)
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		i;
	char				*dest;

	a = ft_strlen(s1);
	b = 1;
	i = 0;
	dest = (char *)malloc(sizeof(char) * ((a + b) + 1));
	if (dest == NULL)
		return (NULL);
	while (i < (a + b))
	{
		if (i < a)
			dest[i] = s1[i];
		else
			dest[i] = c;
		i++;
	}
	dest[i] = '\0';
	free(s1);
	return (dest);
}
/*
	this function will handle the $? case, that should be replaced by the exit status of the last used command
	also it handles the same behaviour as bash, e.g: if we have $?something, it should store the value of $? and ALSO "something"
	so it would for example store: 0something
*/
void	handle_exlamation(t_env *env, char *st, int i)
{
	char	*num;

	num = NULL;
	num = ft_itoa(env->exit_stts);
	env->new_str = ft_strjoin_free(env->new_str, num);
	free(num);
	while (st[i] != ' ' && st[i] != '$' && st[i] != '\0')
	{
		env->new_str = ft_strjoin_c(env->new_str, st[i]);
		i++;
	}
}
