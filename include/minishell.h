/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/19 13:13:06 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include "../libft/include/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <pwd.h>

# define MAX_VAR 1024
# define MAX_PATH 1024
# define MAX_LINE 4096

# define MSHELL "minishell"

# define E_EXE "error occured during execution"
# define E_NOTF "command not found"
# define E_NOTVAL "variable name must begin with a letter."
# define E_ARGNOTVAL "please enter arguments in format 'name=value'."
# define E_NOTALNUM "variable name must contain alphanumeric characters."
# define E_QUOT "invalid quoting, try again"
# define E_NOEX "no such file or directory"
# define E_NOPERM "permission denied"
# define E_NODIR "is not a directory"
# define E_NULLVAR "not set"
# define E_ISDIR "is a directory"
# define E_NOUSER "no such user or named directory"

typedef struct s_env
{
	char	**env;
	char	**path;
}			t_env;

typedef struct s_quotes
{
	int	s_quote;
	int	d_quote;
	int	closed;
}			t_quotes;

typedef struct s_pars
{
	int		len;
	char	**parsed;
	char	*trimmed;
}			t_pars;

typedef struct s_word
{
	int		len;
	int		expan;
	int		k;
}			t_word;

int		check_command(char **input, char **path, char **env);
int		check_exec(char **input, int rb, char **builtins, t_env *env);
int		check_quotes(char *input);
int		do_cd(char **input, t_env *env);
int		do_echo(char **input, t_env *env);
int		do_env(char **input, t_env *env);
int		do_setenv(char **input, t_env *env);
int		do_unsetenv(char **input, t_env *env);
char	*dollar_expansion(char *expanded, char *word, char **env, int len);
void	error_print(char *word, char *command, char *e_msg);
void	get_env(t_env *dest, char **environ, int argc, char **argv);
char	*handle_expansions(char *input, char **env, int *total, int *i);
int		is_expansion(char *str, int i);
char	**parse_input(char *input, char **env);
char	*passwd_user(char *input);
char	*tilde_expansion(char *word, char **env, char *expanded);
void	update_env(char **env, char *input, char *var);
char	*user_expansion(char *input);
void	free_parsed_input(char **p_input);

/***********\
** utils.c **
\***********/
size_t	ft_linecount(char **arr);
void	free_strarr(char **strarr);
int		is_single_quote(char c);
int		is_double_quote(char c);
int		is_quote(char c);

/***********\
** utils2.c **
\***********/
int		check_equalsign(char *input);
int		is_valid_char(char c);
void	add_letter(char *word, char c, int *total, int *k);
int		can_be_added(char c, t_quotes *quots);
int		is_end_of_word(char c, t_quotes *quots);

typedef int					(*t_builtins)(char **input, t_env *env);

static const t_builtins		g_builtins[6] = {
	do_echo,
	do_cd,
	do_setenv,
	do_unsetenv,
	do_env,
	NULL
};
#endif
