/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:10:54 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/07 16:14:53 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

static void	execution(char *cmd, t_data *pipex_args)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_free(ERROR_SPLIT, "", 127, pipex_args);
	if (!cmd_args[0] || cmd[0] == '/' || cmd[0] == '.')
		cmd_path = arg_check(cmd_args, pipex_args, cmd);
	else if (ft_strchr(cmd_args[0], '/'))
		cmd_path = access_flag(cmd_args, pipex_args, 1, cmd);
	else
		cmd_path = verify_cmd_path(cmd_args[0], pipex_args->env_pointer);
	if (cmd_path == NULL)
	{
		split_free(cmd_args);
		error_free(ERROR_CMD, cmd, 127, pipex_args);
	}
	if (execve(cmd_path, cmd_args, pipex_args->env_pointer) == -1)
	{
		split_free(cmd_args);
		free(cmd_path);
		error_free(ERROR_EXECVE, "", 1, pipex_args);
	}
	split_free(cmd_args);
	free(cmd_path);
}

void	first_child(t_data *pipex_args, int pipe_fd[])
{
	int	fd;

	if (close(pipe_fd[0]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	if (dup2(pipe_fd[1], 1) == -1)
		error_free(ERROR_DUP, "", 1, pipex_args);
	if (close(pipe_fd[1]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	fd = open_file(pipex_args->infile, pipex_args);
	if (dup2(fd, 0) == -1)
		error_free(ERROR_DUP, "", 1, pipex_args);
	if (close(fd) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	if (pipex_args->cmd1[0] == '\0')
		error_free(ERROR_PERMISSION, "", 126, pipex_args);
	execution(pipex_args->cmd1, pipex_args);
}

void	second_child(t_data *pipex_args, int pipe_fd[])
{
	int	fd;

	if (close(pipe_fd[1]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	if (dup2(pipe_fd[0], 0) == -1)
		error_free(ERROR_DUP, "", 1, pipex_args);
	if (close(pipe_fd[0]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	fd = write_to_file(pipex_args->outfile, pipex_args);
	if (dup2(fd, 1) == -1)
		error_free(ERROR_DUP, "", 1, pipex_args);
	if (close(fd) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	if (pipex_args->cmd2[0] == '\0')
		error_free(ERROR_PERMISSION, "", 126, pipex_args);
	execution(pipex_args->cmd2, pipex_args);
}

void	parent_process(int pipe_fd[], int pid_2, t_data *pipex_args)
{
	int	child_nmb;
	int	pid;
	int	exit_status;
	int	status;

	status = 0;
	child_nmb = 2;
	if (close(pipe_fd[0]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	if (close(pipe_fd[1]) == -1)
		error_free(ERROR_CLOSE, "", 1, pipex_args);
	while (child_nmb != 0)
	{
		pid = waitpid(-1, &exit_status, 0);
		if ((pid == pid_2) && WIFEXITED(exit_status))
			status = WEXITSTATUS(exit_status);
		child_nmb--;
	}
	free(pipex_args);
	exit(status);
}
