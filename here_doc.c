/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:41:04 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/05 13:54:28 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_should_process = 1;

static void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_should_process = 0;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		printf("\033[1A");
	}
}

static void	here_doc_helper(t_env *env, char *delimiter, char *line_str)
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
				printf("\033[1A\033[2C");
			//PROCESS INPUT HERE
			break ;
		}
		if (!g_should_process)
		{
			g_should_process = 1;
			break ;
		}
		env->all_lines = ft_strjoin_free(env->all_lines, line_str);
		env->all_lines = ft_strjoin_c(env->all_lines, '\n');
		free(line_str);
	}
}

void here_doc(char *st, t_env *env)
{	
	char 	*redir_sign; //<<
	char	*delimiter; // after << 
	char	*line_str;
	int		i;

	i = 0;
	line_str = NULL;
	env->all_lines = ft_strdup(""); //dont forget to free env->all_lines
	redir_sign = ft_strnstr(st, "<<", ft_strlen(st));
	delimiter = redir_sign + 2;
	while (*delimiter == ' ')
		delimiter++;
	here_doc_helper(env, delimiter, line_str);
}

