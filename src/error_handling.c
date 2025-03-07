/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:47:01 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/07 13:34:09 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_free(char *error, char *details, int code, t_data *pipex_args)
{
	if (pipex_args)
		free(pipex_args);
	write(2, error, ft_strlen(error));
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
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
