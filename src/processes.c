/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:10:54 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/06 17:00:00 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>

static void	execution(char *cmd, t_pipex *pipex_args)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_free(ERROR_SPLIT, "", 127, pipex_args);
	if (!cmd_args[0])
	{
		free(cmd_args);
		error_free(ERROR_CMD, "", 127, pipex_args);
	}
	if (cmd[0] == '/')
	{
		cmd_path = cmd_args[0];
		if (access(cmd_path, X_OK) != 0)
		{
			free(cmd_args);
			error_free(ERROR_NOFILE, cmd_path, 127, pipex_args);
		}
	}
	else if ((cmd[0] == '.' && cmd[1] == '/'))
	{
		cmd_path = cmd_args[0];
		if (access(cmd_path, X_OK) != 0)
		{
			free(cmd_args);
			error_free(ERROR_PERMISSION, cmd_path, 126, pipex_args);
		}
	}
	else if (ft_strchr(cmd_args[0], '/'))
	{
		cmd_path = cmd_args[0];
		if (access(cmd_path, F_OK) == -1)
		{
			free(cmd_args);
			error_free(ERROR_NOFILE, cmd_path, 127, pipex_args);
		}
		else if (access(cmd_path, X_OK) != 0)
		{
			free(cmd_args);
			error_free(ERROR_PERMISSION, cmd_path, 126, pipex_args);
		}
	}
	else
		cmd_path = verify_cmd_path(cmd_args[0], pipex_args->env_pointer);
	if (cmd_path == NULL)
	{
		free(cmd_args);
		error_free(ERROR_CMD, "", 127, pipex_args);
	}
	if (execve(cmd_path, cmd_args, pipex_args->env_pointer) == -1)
	{
		free(cmd_args);
		free(cmd_path);
		error_free(ERROR_EXECVE, "", 1, pipex_args);
	}
	split_free(cmd_args);
	free(cmd_path);
}

void	first_child(t_pipex *pipex_args, int pipe_fd[])
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
	execution(pipex_args->cmd1, pipex_args);
}

void	second_child(t_pipex *pipex_args, int pipe_fd[])
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
	execution(pipex_args->cmd2, pipex_args);
}

void	parent_process(int pipe_fd[], int pid_2, t_pipex *pipex_args)
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
