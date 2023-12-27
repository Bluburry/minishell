#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "libft.h"
# include "macros.h"
# include "structures.h"
# include <stdint.h>
# include <term.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>

//# define CTRL_D __IOR(4, 4, int)


extern int	r_sig;

extern int	g_sig;


void	waiting_for_input(t_env *env, t_data *data);
void	env(char **envp);
void	parser(char *input);
void	ft_echo(char **argv);
char	*pwd(void);
void	find_exe(t_tok token, t_data *data);
int		run_exe(char *path, char **args, t_env *env);

// ---change_directory---
// change_directory/cd.c
int		cd(t_env *env, const char *path);
void	alter_paths(t_env *env, char *new_path, char *old_path);
int		home_dir(t_env *env, const char *path);
void	change_pwd(t_env *env, const char *path);

// change_directory/relative_path.c
char	*complex_path(char *pwd, const char *path, int i, int j);
char	*calc_pwd(char *pwd, const char *path);
char	*relative_path(t_env *env, const char *path);

// ---data_structures/---
// data_structures/cmda.c
t_cmda	*create_cmda(uint32_t cap);
void	clean_token_contents(t_tok *token);
void	clean_cmda(t_cmda *cmda);

// data_structures/realloc.c
void	*ft_reallocation(void *ptr, size_t ptrsize, size_t size);

// ---lexer/---
// lexer/expand_var_tokens.c
int		count_tokens(char **input);
char	**expand_var_tokens(char **input, t_env *env);

// lexer/lexer_utils.c
//Signal functions
void	sig_handler_interrupt(int sig, siginfo_t *info, void *ucontext);
void	sig_handler_fork(int sig);
void	set_signals_base(void);
void	set_signals_fork(void);
void	init_child_signals(void);

//Lexer functions
// lexer/lexer.c
char	**lexer(char *input, t_env *env, t_data *data);
void	syntax_error(int type, char c);
void	dcp_cleaner(char **ptr);
char	**check_for_quotes(char *input, char **ptr, int *flag);
int		is_space(char c);

// lexer/merge_tokens_cleanup.c
char	**merge_tokens_cleanup(char **input);
int		count_merge_tokens(char **input);
int		is_operator(char c, char *operators);

// lexer/space_tokens_cleanup.c
char	**space_tokens_cleanup(char **input);
int		count_space_tokens(char **input);

// lexer/split_char_tokens.c
char	**split_char_tokens(char **input, char c);
char	**tokenize_char(char *input, char **ptr, char c);
int		count_char_tokens(char **input, char c);
char	*sdf(char *tmp, char c, int *len);
int		find_char(char *str, char c);

// lexer/split_inout_tokens.c
char	**split_inout_tokens(char **input);
char	**tokenize_inout(char *input, char **ptr);
int		count_inout_tokens(char **input);
int		count_inouts(char *str, char c);

// lexer/split_quote_tokens.c
char	**split_quotes_tokens(char *input);
char	check_if_valid(char *ptr);
int		quotes_end(char *input);
int		count_tokens_quotes(char *input);

// lexer/split_tokens.c
char	**tokens_init(char *input, t_env *env);
void	remove_quotes_from_tokens(char **input);
char	*create_token(const char *str, size_t len);
int		move_in_str(char *str, char c);
int		is_token_end(char c);

// lexer/var_to_value.c
char	*var_to_value(char *str, t_env *env);

// ---parser/---
// parser/create_comms.c
uint32_t	list_len(char **list);
bool		create_comm_list(t_data *data);

//parser/exec_comms.c
bool	exec_comm_list(t_data *data);

// parser/insert_args.c
bool	insert_name_args(t_cmda *cmds, char **list, uint32_t n);

// parser/insert_redirs.c
bool	insert_redirs(t_cmda *cmds, char **list, uint32_t n);

// ---struct_handling/---
//Environment variables functions
double	total_size(char **mat, int size);
void	concatenate_matrix(char *str, char **mat, int size);

// struct_handling/alter_env.c
int		alter_env_var(t_env *env, char **new);
void	resize_env_struct(t_env *env, int inc);
void	replace_env_var(t_env *env, const char *new, int i);

// struct_handling/clear_env.c
void	unset_env_var(t_env *env, char **var);
void	clear_chars(char **str, int size);
void	clear_env_struct(t_env *env);

// struct_handling/find_env_var.c
char	*str_after_char(char *str, char c);
int		ft_strchrstr(const char *str, char c, const char *str_find);
int		index_of_str(t_env *env, const char *str);
char	*get_env_var(t_env *env, const char *str);

// struct_handling/print_env.c
int		var_to_print(char *str);
int		num_invalid_env_vars(t_env *env);
void	copy_char_to_env(char **mat, char **new_mat, int size);
char	**env_string(t_env *env);

// struct_handling/print_export.c
int		str_cmp(const char *str1, const char *str2);
int		ordered_index(char **strs, int size, int prev);
void	memcpy_export(char *dest, char *src, int n);
void	copy_char_matrix_ordered(char **mat, char **new_mat, int size);
char	**export_string(t_env *env);

// struct_handling/start_env_vars.c
void	copy_char_matrix(char **mat, char **new_mat, int size);
int		get_env_start_size(char **envp);
t_env	*create_env_struct(char **envp);

// ---utils/---
// utils/echo.c
void	ft_echo(char **argv);

// utils/env.c
void	env(char **envp);

// utils/pwd.c
char	*pwd(void);

// utils/signal_handler.c
void	set_signals_base(void);
void	sig_handler_interrupt(int sig, siginfo_t *info, void *ucontext);

// utils/utils.c
int		check_path(char *path);
bool	is_metachar(char c);
bool	is_name(char *str);

// utils/find_exe.c
char	*create_exec_string(const char *path, const char *cmd, int start, int end);
int		check_file_executable(struct stat *bs, char *exec);
char	*handle_exe_stats(const char *path, char *cmd, struct stat *bs);
char	*find_exe_path(t_env *env, char *cmd);

#endif
