/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:15:56 by corellan          #+#    #+#             */
/*   Updated: 2023/03/13 15:00:36 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/errno.h>
# define BUFFER 1024

typedef struct s_env
{
	char	**env;
	char	oldpwd[BUFFER];
	char	newpwd[BUFFER];
	int		level;
	int		flag;
    char    *var_value;
}	t_env;

typedef struct s_sp_arg
{
	int		p;
	int		q;
	int		t;
	size_t	i;
	size_t	j;
	size_t	len;
}	t_sp_arg;

typedef struct s_echo
{
	int				pos;
	struct s_echo	*next;
}	t_echo;

void		ft_copy_env(t_env *env, char **envp);
void		handle_shortcuts(void);
void 		handle_ctrlD(void);
int			ft_wordcount_argc(char const *str);
int			ft_count_space(char const *str);
long long	ft_atoll(char const *str);
int			ft_am_i_valid_number(char const *str);
int			ft_am_i_a_number(char *str);
int			ft_line_checker(char *s, int *ret, t_env *env);
int			ft_check_symbols(char const *str);
int			ft_exit_check(char *str, int *ret);
char		**ft_custom_split(char const *s);
int			ft_check_single_quot(char const *str, int *i, int *j);
int			ft_check_double_quot(char const *str, int *i, int *j);
size_t		ft_len_single_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_len_double_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_count_char_arg(char const *str);
char		**ft_custom_split_free(char **array, size_t i);
size_t		ft_strlcpy_arg(char *d, char const *s, size_t size, t_sp_arg *sp);
int			ft_echo(char *str);
int			ft_check_s_quot_echo(char const *str, int *i, int *j, t_echo **e);
int			ft_check_d_quot_echo(char const *str, int *i, int *j, t_echo **e);
void		ft_add_to_list(t_echo **begin, int num);
int			ft_listsize(t_echo **lst);
void		ft_free_list(t_echo **lst);
void		ft_print_list(t_echo **a);
int			ft_pwd(void);
int			ft_cd(char *s, int i, t_env *env);
int			ft_env(t_env *env);
void		ft_add_variables(t_env *env, char *variable);
int			check_dollar(char *s, t_env *env);
#endif