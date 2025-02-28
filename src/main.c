/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:58 by ekashirs          #+#    #+#             */
/*   Updated: 2025/02/28 15:16:26 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv, char **envp)
{
	int	pipe_fd[2];
	pid_t	id;

	if (argc != 5)
		error_exit(1);
	if (check_args(argv))
		error_exit(2);
	if (parse_args(argv))
		error_exit(3);
	id = fork();
	if (id == -1)
		error_exit(4);
	if (id == 0)
		child_process(argv[1], argv[2], envp, pipe_fd);
	waitid(id, NULL, 0);
	parent_process(argv[3], argv[4], envp, pipe_fd);
	return (0);
}
