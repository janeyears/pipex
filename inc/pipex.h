/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:48 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/06 16:32:39 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# define ERROR_ARGS "Usage: ./pipex infile cmd1 cmd2 outfile"
# define ERROR_PIPE "./pipex: pipe creation failed"
# define ERROR_CALLOC "./pipex: ft_calloc function has failed"
# define ERROR_FORK "./pipex: fork failed"
# define ERROR_CMD "./pipex: command not found: "
# define ERROR_DUP "./pipex: dup2 function has failed"
# define ERROR_CLOSE "./pipex: close function has failed"
# define ERROR_EXECVE "./pipex: execve function has failed"
# define ERROR_SPLIT "./pipex: ft_split function has failed"
# define ERROR_PERMISSION "./pipex: permission denied "
# define ERROR_NOFILE "./pipex: no such file or directory: "

typedef struct s_pipex
{
	char	**env_pointer;
	char	*infile;
	char	*cmd1;
	char	*outfile;
	char	*cmd2;
}	t_pipex;

void	first_child(t_pipex *pipex_args, int pipe_fd[]);
void	second_child(t_pipex *pipex_args, int pipe_fd[]);
void	parent_process(int pipe_fd[], int pid_2, t_pipex *pipex_args);
char	*verify_cmd_path(char *cmd, char **envp);
int		open_file(char *file, t_pipex *pipex_args);
int		write_to_file(char *file, t_pipex *pipex_args);
void	error_free(char *error, char *details, int code, t_pipex *pipex_args);
void	split_free(char **array);

#endif