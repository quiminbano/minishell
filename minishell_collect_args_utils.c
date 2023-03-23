/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:07:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/23 15:11:54 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_var_available(char *substr, t_env *env)
{
	int		i;
	char	*var;
	char	*add_equal;

	add_equal = ft_strjoin(substr, "=");
	i = 0;
	var = NULL;
	while (env->env[i])
	{
		if ((var = ft_strnstr(env->env[i], add_equal, ft_strlen(add_equal))))
		{
			free(add_equal);
			return (var);
		}
		i++;
	}
	free(add_equal);
	return (NULL);
}

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


