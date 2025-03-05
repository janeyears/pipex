/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:58 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/05 11:14:15 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <sys/types.h>

static void	struct_init(t_pipex *pipex_args, char **argv, char **envp)
{
	if (!argv[2] || argv[2][0] == '\0' || !argv[3] || argv[3][0] == '\0')
		error_free(ERROR_PERMISSION, "", 127, pipex_args);
	pipex_args->infile = argv[1];
	pipex_args->cmd1 = argv[2];
	pipex_args->cmd2 = argv[3];
	pipex_args->outfile = argv[4];
	pipex_args->env_pointer = envp;
}

static void	process_managment(t_pipex *pipex_args, int pipe_fd[])
{
	pid_t	pid_1;
	pid_t	pid_2;

	pid_1 = fork();
	if (pid_1 == -1)
		error_free(ERROR_FORK, "", 1, pipex_args);
	if (pid_1 == 0)
		first_child(pipex_args, pipe_fd);
	pid_2 = fork();
	if (pid_2 == -1)
		error_free(ERROR_FORK, "", 1, pipex_args);
	if (pid_2 == 0)
		second_child(pipex_args, pipe_fd);
	parent_process(pipe_fd, pid_2, pipex_args);
}

int main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	t_pipex	*pipex_args;

	pipex_args = NULL;
	if (argc != 5)
		error_free(ERROR_ARGS, "", 1, pipex_args);
	pipex_args = ft_calloc(1, sizeof(t_pipex));
	if (pipex_args == NULL)
		error_free(ERROR_CALLOC, "", 1, pipex_args);
	struct_init(pipex_args, argv, envp);
	if (pipe(pipe_fd) == -1)
		error_free(ERROR_PIPE, "", 1, pipex_args);
	process_managment(pipex_args, pipe_fd);
	return (0);
}
