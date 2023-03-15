/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_collect_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:35:50 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/15 15:42:21 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	returns the index of the first dollar sign.
*/
static int dollar_idx(char *substr)
{
	int	i;

	i = 0;
	while (substr[i] != '$')
		i++;
	return (i);
}

/*
	checks if the text after $ is a valid env arg or not.
	If so, it will replace it with the right var value, else,
	it will just add nothing, (an empty string);
*/
static void	parse_substr(char **substrs, t_env *env)
{
	int	i;

	i = 0;
	while (substrs[i])
	{
		if (getenv(substrs[i]))
			env->new_str = ft_strjoin(env->new_str, getenv(substrs[i]));
		else
			env->new_str = ft_strjoin(env->new_str, "");
		i++;
	}
}

/*
	this function takes each substring containing 1 or more $ sign and process it.
	
	if the substring starts with a $ sign, that means we might have : $VAR or $VAR1$VAR2$VAR3...
	so it takes the substring and splits it again, with '$' as 
	delimiter, and checks each text after each $.
	if this text is a valid env arg, it will replace it with it's value, and append to env->new__str, 
	if not, it will just append an empty str.

	if the substring doesnt start with a $ sign, example hello$VAR1$VAR2, the function will process
	the first part first "hello" and append it to env->new_str, and then takes the rest $VAR1$VAR2
	and splits it, and goes through each text after each $ to check if its a valid env ARG or NOT

*/
static void	process_substr(char *substr, t_env *env)
{
	char	i;
	char	**substrs;
	char	*first_part;

	first_part = strdup("");
	if (substr[0] == '$')
	{
		substrs = ft_split(substr, '$');
		parse_substr(substrs, env);
	}
	else
	{
		i = dollar_idx(substr);
		ft_strlcpy(first_part, substr, i + 1);
		env->new_str = ft_strjoin(env->new_str, first_part);
		substrs = ft_split(substr + i, '$');
		parse_substr(substrs, env);
	}
	//This is used to print a $ sign, in case there was one at the end of a var or a sequence of
	//vars, to match the behaviour of bash
	//e.g, in bash: $VAR$ will print the value of VAR + $.
	if (substr[ft_strlen(substr) - 1] == '$')
		env->new_str = ft_strjoin(env->new_str, "$");
	free(first_part);
	ft_free_split(substrs);
}

/*
	this function will parse each substring taken from the string.
	If the substring doesnt have a $ sign in it, it will join it to env->new_str the way it is.
	if it has a $ sign, it will call process_susbtr.
*/
static void	parse_str(char **split_str, t_env *env)
{
	int		i;

	i = 0;
	env->new_str = ft_strdup("");
	while(split_str[i])
	{
		if (ft_strchr(split_str[i], '$'))
			{
				process_substr(split_str[i], env);
			}
		else
		{
			env->new_str = ft_strjoin(env->new_str, split_str[i]);
		}
		env->new_str = ft_strjoin(env->new_str, " ");
		i++;
	}
}

/*
	this function is called from linechecker, after adding str to history, this function will 
	take the str from readline, and replace it with env->new_str, that will take str, 
	replicate it, while replacing every $VAR with it's correspondant value if possible, and
	ignoring non existing $VARS

	This function will take the input, and use ' ' as a splitting delimiter, and store the substrings
	in a 2D array.
*/
void	collect_args(char *s, t_env *env)
{
	char	**split_str;

	split_str = ft_split(s, ' ');
	parse_str(split_str, env);
	ft_free_split(split_str);
}