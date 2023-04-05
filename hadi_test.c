/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hadi_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:41:04 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/04 13:18:44 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//handle ctrl+D
	// not empty = nothing
	// empty = process and exit

//handle ctrl+C
	// not empty = just exit
	// emmpty = just exit

#include "minishell.h"

void testing_func(char *st, t_env *env)
{	
	char *redir_sign;
	char *delimiter;
	char *line_str;

	env->all_lines = ft_strdup(""); //dont forget to free env->all_lines
	redir_sign = ft_strnstr(st, "<<", ft_strlen(st));
	delimiter = redir_sign + 2;

	while (*delimiter == ' ')
		delimiter++;
	while (1)
	{
		line_str = readline("> ");
		if (!line_str || ft_strncmp(delimiter, line_str, ft_strlen(delimiter)) == 0)
		{
			//printf("%s", env->all_lines);
			break;
		}
		//signal(SIGINT, here_doc_stop);
		signal(SIGQUIT, SIG_IGN);
		env->all_lines = ft_strjoin_free(env->all_lines, line_str);
		env->all_lines = ft_strjoin_c(env->all_lines, '\n');
		free(line_str);
	}
	return;
}