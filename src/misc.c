/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:00:57 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/07 16:10:34 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

int	open_file(char *file, t_data *pipex_args)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
		error_free(ERROR_PERMISSION, file, 1, pipex_args);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_free(ERROR_NOFILE, file, 127, pipex_args);
	return (fd);
}

int	write_to_file(char *file, t_data *pipex_args)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error_free(ERROR_PERMISSION, file, 1, pipex_args);
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
		error_free(ERROR_NOFILE, file, 127, pipex_args);
	return (fd);
}

char	*access_flag(char **cmd_args, t_data *pipex_args, int flag, char *cmd)
{
	char	*cmd_path;

	cmd_path = cmd_args[0];
	if (flag && access(cmd_path, F_OK) == -1)
	{
		split_free(cmd_args);
		error_free(ERROR_NOFILE, cmd, 127, pipex_args);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		split_free(cmd_args);
		error_free(ERROR_PERMISSION, cmd, 126, pipex_args);
	}
	return (cmd_path);
}

char	*arg_check(char **cmd_args, t_data *pipex_args, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!cmd_args[0])
	{
		free(cmd_args);
		error_free(ERROR_CMD, cmd_path, 127, pipex_args);
	}
	if (cmd[0] == '/')
		cmd_path = access_flag(cmd_args, pipex_args, 1, cmd);
	else if (cmd[0] == '.' && cmd[1] == '/')
		cmd_path = access_flag(cmd_args, pipex_args, 0, cmd);
	return (cmd_path);
}
