/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:35:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/23 15:19:53 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	collect_args(char *st, t_env *env)
{
	int	is_inside;
	int	i;
	int	last_idx;
	int	var_len;
	char	*var_name;
	char	*var_value;

	var_name = strdup("");
	var_len = 0;
	last_idx = 0;
	i = 0;
	is_inside = 0;

	while (st[i])
	{
		if (st[i] == '\'' && !is_inside)
		{
			is_inside = 1;
			i++;
		}
		else if (st[i] == '\'' && is_inside)
		{
			is_inside = 0;
			i++;
		}
		else if (st[i] == '$' && (st[i + 1] == ' ' || st[i + 1] == '\0'))
		{
			env->new_str = ft_strjoin_c(env->new_str, '$');
			i++;
		}
		else
		{
			if (st[i] == '$' && !is_inside)
			{
				i++;
				last_idx = i;
				while (st[last_idx] != ' ' && st[last_idx] != '\'' && st[last_idx] != '\0' && st[last_idx] != '$' && st[last_idx] != '\"')
					last_idx++;
				var_len = last_idx - i + 1;
				ft_strlcpy(var_name, (st + i), var_len);
				if ((var_value = is_var_available(var_name, env)))
				{
					env->new_str = ft_strjoin_free(env->new_str, var_value + var_len);
				}
				else if (st[i]== '?')
				{
					i++;
					handle_exlamation(env, st, i);
				}
				else
					env->new_str = ft_strjoin_free(env->new_str, "");
				i = last_idx;
			}
			else
			{
				env->new_str = ft_strjoin_c(env->new_str, st[i]);
				i++;
			}
		}
	}
}