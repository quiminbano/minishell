/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shortcuts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:26:40 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/04/10 13:39:54 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals2(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit: 3\n", 8);
		kill(g_should_process, SIGQUIT);
		g_should_process = 0;
	}
	if (sig == SIGINT)
	{
		kill(g_should_process, SIGINT);
		g_should_process = 0;
	}
}

void	handle_shortcuts2(void)
{
	signal(SIGQUIT, &handle_signals2);
	signal(SIGINT, &handle_signals2);
}

int	handle_ctrl_d(char *str, t_env *env)
{
	printf("\033[1A");
	printf("\033[11C");
	printf("exit\n");
	free(str);
	ft_free_split(env->env);
	free(env->new_str);
	return (0);
}

static void	sigint_func(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	handle_shortcuts(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_func);
}
