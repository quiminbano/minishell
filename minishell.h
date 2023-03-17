/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:15:56 by corellan          #+#    #+#             */
/*   Updated: 2023/03/17 15:13:49 by corellan         ###   ########.fr       */
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
	char	*new_str;
	int		set_f;
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

typedef struct s_args
{
	int				pos;
	struct s_args	*next;
}	t_args;

typedef struct s_export
{
	int				index;
	struct s_export *next;
}	t_export;

void		ft_copy_env(t_env *env, char **envp);
void		handle_shortcuts(void);
int 		handle_ctrlD(char *str);
int			ft_wordcount_argc(char const *str);
int			ft_find_word_array(char **array, char *needle);
int			ft_array_len(char **array);
long long	ft_atoll(char const *str);
int			ft_am_i_valid_number(char const *str);
int			ft_am_i_a_number(char *str);
int			ft_line_checker(char *st, int *ret, t_env *env);
int			ft_check_symbols(char const *str);
int			ft_exit_check(char **array, char *str, int *ret, t_env *env);
char		**ft_custom_split(char const *s);
int			ft_check_single_quot(char const *str, int *i, int *j);
int			ft_check_double_quot(char const *str, int *i, int *j);
size_t		ft_len_single_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_len_double_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_count_char_arg(char const *str);
char		**ft_custom_split_free(char **array, size_t i);
size_t		ft_strlcpy_arg(char *d, char const *s, size_t size, t_sp_arg *sp);
int			ft_echo(char **array);
size_t		ft_wordcount_args(char const *str, t_args **args);
void		ft_add_to_list_args(t_args **begin, int num);
int			ft_listsize_args(t_args **lst);
void		ft_free_list_args(t_args **lst);
void		ft_print_list_args(t_args **a);
int			ft_pwd(void);
int			ft_cd(char **path, t_env *env);
int			ft_env(t_env *env);
void		ft_add_variables(t_env *env, char *variable);
void		ft_add_variables_copy_back(t_env *env, char **array, int i);
void		collect_args(char *st, t_env *env);
int			ft_export(t_env *env, char **array);
void		ft_add_to_list_export(t_export **begin, int num);
int			ft_listsize_export(t_export **lst);
void		ft_free_list_export(t_export **lst);
void		ft_decide_what_print(char **array, t_export **exp);
void		ft_sort_and_print_strings(char **array);
void		ft_putstr_export(char *st, int fd);
int			ft_check_first_variable(char *variable);
void		ft_print_list_export(t_export **a);
int			ft_unset(t_env *env, char **array);

#endif