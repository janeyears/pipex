/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:08:34 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/28 14:42:09 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_read_line(char **buffer, int fd)
{
	char	*tmp_buff;
	char	*tmp_line;
	int		bytes;

	tmp_buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (tmp_buff == NULL)
		return ;
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, tmp_buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp_buff);
			return ;
		}
		tmp_buff[bytes] = '\0';
		tmp_line = ft_strjoin(*buffer, tmp_buff);
		free(*buffer);
		*buffer = tmp_line;
		if (ft_strchr(tmp_buff, '\n'))
			break ;
	}
	free(tmp_buff);
}

void	ft_extract_line(char **buffer, char **line, size_t len)
{
	char	*remaining_data;
	size_t	i;

	*line = ft_calloc(len + 2, sizeof(char));
	if (!(*line))
		return ;
	i = 0;
	while (i < len)
	{
		(*line)[i] = (*buffer)[i];
		i++;
	}
	if ((*buffer)[i] == '\n')
		(*line)[i++] = '\n';
	(*line)[i] = '\0';
	if ((*buffer)[i])
	{
		remaining_data = ft_strjoin(*buffer + i, "");
		free(*buffer);
		*buffer = remaining_data;
		return ;
	}
	free(*buffer);
	*buffer = NULL;
}
