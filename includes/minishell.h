/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:56:50 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/08 13:49:11 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/param.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define PROMPT "minishell: "
# define HOME_ENV "HOME"
# define OLD_PWD_ENV "OLDPWD"
# define CMD_NOT_FOUND_ERROR 127
# define CMD_NOT_EXECUTABLE_ERROR 126
# define HEREDOC_NAME "/tmp/.temp_heredoc_"

typedef struct s_ios
{
	int		fd_input;
	int		fd_output;
	int		stdin_backup;
	int		stdout_backup;
	char	*infile_name;
	char	*outfile_name;
	char	*heredoc_delimiter;
	bool	has_heredoc_quotes;
}	t_ios;

typedef struct s_token // struct for the tokens
{
	char			*token;
	char			*token_backup;
	int				type;
	int				status;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_list
{
	char			*name;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_pre_command
{
	char					*command;
	char					*path;
	char					**args_array;
	bool					is_pipe_output;
	t_ios					*io_fds;
	int						*pipe_fd;
	struct s_pre_command	*next;
	struct s_pre_command	*prev;
}	t_pre_command;

typedef struct s_config
{
	t_pre_command	*pre_cmds;
	char			*command_input;
	t_token			*token_list;
	char			*working_dir;
	char			*old_working_dir;
	bool			is_interactive;
	t_list			*ls_env;
	t_list			*ls_exp;
	int				error_code;
	pid_t			process_id;
}	t_config;

//ENUMS
enum e_tokens {
	WORD,
	SPACES,
	VAR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE_DOC,
	END_OF_FILE,
};

enum e_quotes {
	SINGLEQ,
	DOUBLEQ,
	NOQUOTE,
};

/* -------------------------- Auxiliary Functions -------------------------- */
int				ft_isspace(int c);
int				ft_only_spaces(char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
size_t			ft_strlen(const char *str);
void			*ft_memset(void *b, int symbol, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *str1, const char *str2, size_t num);
char			*ft_strchr(const char *str, int c);
char			*ft_strjoin(char const *s1, char const *s2);
t_token			*lst_new_token(char *str, int type, int status);
void			lst_add_back_token(t_token **alst, t_token *new_node);
char			*ft_strdup(const char *s);
t_pre_command	*lst_new_command(bool value);
void			lst_add_back_cmd(t_pre_command **list, t_pre_command *new_cmd);
t_pre_command	*lst_last_cmd(t_pre_command *cmd);
void			lst_clear_token(t_token **lst);
int				lst_size_cmd(t_pre_command *cmd);
void			ft_putstr_fd(char *str, int fd);
int				ft_lstsize(t_list *lst);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_atoi_long(const char *str, bool *error);
char			**allocate_str_array(const char *str, char c);
char			**split_str(const char *str, char c, char **arr_str);

/* ----------------------------- Execution Part ----------------------------- */
int				ms_execute(t_config *config);
t_list			*ft_lstnew(char *name, char *value);
void			ft_lstdelone(t_list *lst);
void			ft_lstclear(t_list **lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_set_signal_handlers(t_config *config);
bool			get_heredoc(t_config *data, t_ios *io);
int				set_env(t_config *config, char *name, char *value);
void			ft_putendl_fd(char *s, int fd);
void			display_error(char *command, char *error_message);
void			display_detailed_err(char *command, char *detail,
					char *error_message);
bool			redirect_io(t_ios *io);
bool			restore_io(t_ios *io);
void			close_pipe_fds(t_pre_command *cmds, t_pre_command *skip_cmd);
void			free_data(t_config *data, bool clear_history);
void			close_fds(t_pre_command *cmds, bool close_backups);
bool			create_pipes(t_config *data);
bool			cmd_is_dir(char *cmd);
int				check_command_not_found(t_config *data, t_pre_command *cmd);
void			exit_shell(t_config *data, int exno);
bool			check_infile_outfile(t_ios *io);
bool			set_pipe_fds(t_pre_command *cmds, t_pre_command *c);
int				execute_command(t_config *data, t_pre_command *cmd);
int				execute_builtin(t_config *data, t_pre_command *cmd);
t_config		*get_config_instance(t_config *config);
void			ft_exit(int signal);
void			free_pre_cmd_list(t_pre_command **lst);

/* ----------------------------- Builtins Part ----------------------------- */
int				env_builtin(t_config *data, char **args);
int				pwd_builtin(t_config *config);
int				echo_builtin(char **args);
int				export_builtin(t_config *data, char **args);
int				unset_builtin(t_config *config, char **args);
int				cd_builtin(t_config *config, char **args);
int				exit_builtin(t_config *data, char **args);
bool			is_dest_home(char *const *args);
void			update_wds(t_config *data, char *wd);
bool			chdir_errno_mod(char *path);
void			build_env_string(const t_list *env_item, char *line_name);

/* ----------------------------- Parsing Part ----------------------------- */
void			ft_build_commands(t_config *config);
void			init_env(char **env, t_config *config);
int				ft_parse_input(t_config *config);
int				ft_get_separator(char *str, int i);
int				ft_check_quotes(char c, int quotecheck);
bool			ft_tokenization(t_config *config);
void			ft_expand_all_variables(t_config *config);
void			ft_quotes_removal(t_config *config);
void			free_str_array(char **str_array);
void			free_config(t_config *config);
void			rl_replace_line(const char *text, int clear_undo);
char			*find_env(t_config *config, char *env_name);
int				check_pipe_and_redir(t_config *config);
char			*ft_retrieve_env_value(t_config *config, char *str);
void			replace_variable(t_token *token_node, char *env_value,
					int index);
void			erase_variable(t_token *token_node, int index);
void			free_args(char **args);
void			free_str_tab(char **tab);
char			*get_cmd_path(t_config *data, char *name);
bool			is_valid_env(char *var);
void			init_wd(t_config *data);
char			**env_to_array(t_config *data);
void			init_io(t_pre_command *cmd);
bool			remove_old_file_ref(t_ios *io, bool infile);
char			*var_expander_heredoc(t_config *data, char *str);
bool			fill_heredoc(t_config *data, t_ios *io, int fd);
void			prep_no_arg_commands(t_config *data);
int				validate_quote(char *s, int start, int end);
int				count_len(char *str, int count, int i);
void			change_status_to_quote(t_token **token_node, int *i);
char			*ft_extract_var(char *str);
void			str_update(char *new_str, char *var_value, int *j);
int				ft_variable_len(char *str);
void			ft_replace(t_token *token, char *env_value, int index);
bool			is_next_char_a_sep(char c);
bool			var_between_quotes(char *str, int i);
char			*generate_new_token_string(char *old, char *var_value,
					int len, int index);
char			*erase_and_replace(t_token **token_node, char *str,
					char *var_value, int index);
void			free_io(t_ios *io);
int				ft_check_quotes(char c, int quotecheck);

/* ----------------------------- Syntax Part ----------------------------- */

int				set_arguments(t_token **token_lst, t_pre_command *cmd);
int				count_arguments(t_token *temp);
void			lst_add_new_token(t_token **token_lst,
					char *token_name, int type, int status);
void			syntax_append(t_pre_command **cmd, t_token **token);
void			syntax_pipe(t_pre_command **cmd, t_token **token);
void			heredoc_message(void);
void			syntax_here_doc(t_config *data, t_pre_command **cmd,
					t_token **token);
void			syntax_redir_in(t_pre_command **cmd, t_token **token);
void			syntax_redir_out(t_pre_command **cmd, t_token **token);
void			syntax_word(t_pre_command **command, t_token **token);
void			free_pointer(void *ptr);

#endif

/*
MAXPATHLEN is defined in sys/param.h and is the maximum length of a path in
the system, which is 1024 bytes (including the null terminator).

char			*ft_strjoin(char const *s1, char const *s2);
// join two strings
char			*ft_strjoin2(char const *s1, char const *s2);
// join two strings with a '='
char			*ft_strjoin3(char const *s1, char const *s2);
// join two strings with a '/'
char			*ft_strjoin4(char const *s1, char const *s2, char c)
// join two strings with a char (e.g. '\n')

*/
