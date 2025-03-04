/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:00:57 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/04 17:21:13 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

int	open_file(char *file, t_pipex *pipex_args)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
		error_free(ERROR_PERMISSION, file, 1, pipex_args);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_free(ERROR_NOFILE, file, 127, pipex_args);
	return(fd);
}

int	write_file(char *file, t_pipex *pipex_args)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		error_free(ERROR_PERMISSION, file, 1, pipex_args);
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
		error_free(ERROR_NOFILE, file, 127, pipex_args); // echo $?
	return(fd);
}