/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:41:04 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/10 14:23:35 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_should_process = 0;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		printf("\033[1A");
	}
}

static void	h_doc_helper(t_env *env, char *delimiter, char *line_str)
{
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, handle_sig);
		line_str = readline("> ");
		if ((!line_str || \
			ft_strncmp(delimiter, line_str, ft_strlen(delimiter)) == 0) && \
				g_should_process)
		{
			if (!line_str)
			{
				// printf("XX");
			}
			free(line_str);
			break ;
		}
		if (!g_should_process)
		{
			free(line_str);
			break ;
		}
		env->all_lines = ft_strjoin_free(env->all_lines, line_str);
		env->all_lines = ft_strjoin_c(env->all_lines, '\n');
		free(line_str);
	}
}

void	here_doc(char **st, t_env *env)
{	
	char	*line_str;
	char	**temp;

	line_str = NULL;
	temp = ft_custom_split((*st));
	temp = ft_process_arg(temp, (*st));
	env->all_lines = ft_strdup("");
	h_doc_helper(env, temp[0], line_str);
	ft_free_split(temp);
	free((*st));
	(*st) = ft_strdup(env->all_lines);
	free(env->all_lines);
}
