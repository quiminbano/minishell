/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shortcuts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:26:40 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/07 16:53:45 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_func(int sig)
{
	if (sig == SIGINT)
	{
		//replace content on current line with empty string so current line wont be loged in history
		rl_replace_line("", 0); 
		//inject a \n input
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//moves cursor to next line
		rl_on_new_line();
	}
}

void	handle_shortcuts(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_func);
}

