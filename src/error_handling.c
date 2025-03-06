/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:47:01 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/06 13:12:21 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	error_free(char *error, char *details, int code, t_pipex *pipex_args)
{
	if (pipex_args)
		free(pipex_args);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(details, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	split_free(char **array)
{
	int	i;

	i = 0;
	if (array[i] == NULL)
	{
		free(array);
		return ;
	}
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
