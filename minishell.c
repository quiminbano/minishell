/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/10 14:00:48 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function clears the screen when the program is started. Also, it prints
the welcome message to the user */

static int	ft_start(void)
{
	pid_t		pid;
	char		**str;
	extern char	**environ;

	str = ft_split("clear", ' ');
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execve("/usr/bin/clear", str, environ);
	else
	{
		wait(NULL);
		ft_free_split(str);
		printf("Welcome to minishell. Developed by corellan and hel-hosr. ");
		printf("Hive Helsinki. 2023.\n");
	}
	return (0);
}

/*This function initialize the shell and initialize the while loop to write
text until the user decides to exit the program. This text is gathered through
the readline function and this function prints the prompt minishell$ everytime
that the user writes text. In the current state that this function is, this
function also checks if the user writes the command exit as text, and resolves
the value that the minishell should return depending what the user writes after
the command exit. If the user writes exit + a number between MIN_LONG_LONG and
MAX_LONG_LONG, minishell returns the written number (exit.ret) casted as an 
unsigned char number. If the user writes just exit, the minishell returns 0. 
If the user writes exit + a text message or numbers under LONG_LONG_MIN or 
numbers bigger than LONG_LONG_MAX, the minishell doesn't exit and it continues
working.*/

int	main(void)
{
	char	*str;
	t_exit	exit;

	if (ft_start() == 1)
		return (1);
	while (1)
	{
		handle_shortcuts();
		str = readline("minishell$ ");
		exit.r = ft_line_checker(str, &(exit.ret));
		if (exit.r == 0)
			return (0);
		else if (exit.r == 1)
			return (exit.ret);
		else if (exit.r == 2)
			return (255);
		else if (exit.r == 3)
		{
			//printf("%s\n", str);
			free(str);
		}
	}
	return (0);
}
