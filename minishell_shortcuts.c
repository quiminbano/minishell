/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_shortcuts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:26:40 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/20 14:44:05 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	this function is called from ft_line_checker, when line is empty
	it will reposition the cursor at the end of the previous line (after it automatically moved to the next line)
	and will print "exit" and exit
*/
int handle_ctrlD(char *str, t_env *env)
{
	printf("\033[1A");
	printf("\033[11C");
	printf("exit\n");
	free(str);
	ft_free_split(env->env);
	free(env->new_str);
	return(0);
}

static void	sigint_func(int sig)
{
	if (sig == SIGINT)
	{
		//replace content on current line with empty string so current line wont be loged in history
		rl_replace_line("", 1); 
		//inject a \n input
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//moves cursor to next line
		rl_on_new_line();
	}
}

/*	-first line ignores the signal SIGQUIT produced by CTRL + \
	-second line calls the function, sigint_func when SIGINT is received (SIGINT is sent when 
	the user presses CTR + C)
*/
void	handle_shortcuts(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_func);
}

