/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:52:47 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/04 16:55:02 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <stdlib.h>

static char	*get_path(char **envp)
{
	while(*envp)
	{
		if (!ft_strncmp("PATH", *envp, 5))
			return(*envp + 5);
		envp++;
	}
	return (NULL);
}
static char	*combine_path(char *ret_path, char *splited_path, char *cmd, size_t full_path_len)
{
		ft_strlcpy(ret_path, splited_path, full_path_len);
		ft_strlcat(ret_path, "/", full_path_len);
		ft_strlcat(ret_path, cmd, full_path_len);
		return(ret_path);
}

static char	*check_access(char **splited_paths, char *cmd)
{
	int		i;
	char	*ret_path;
	size_t	full_path_len;

	i = 0;
	while (splited_paths[i])
	{
		full_path_len = ft_strlen(splited_paths[i]) + ft_strlen(cmd) + 2;
		ret_path = ft_calloc(1, sizeof(char) * full_path_len);
		if (ret_path == NULL)
		{
			split_free(splited_paths);
			return (NULL);
		}
		ret_path = combine_path(ret_path, splited_paths[i], cmd, full_path_len);
		if (access(ret_path, X_OK) == 0)
		{
			split_free(splited_paths);
			return (ret_path);
		}
		free(ret_path);
		i++;
	}
	split_free(splited_paths);
	return (NULL);
}

char	*verify_cmd_path(char *cmd, char **envp)
{
	char	*path_str;
	char	**splited_paths;
	char	*res_path;
	int		i;

	path_str = get_path(envp);
	if (path_str == NULL)
		return (NULL);
	splited_paths = ft_split(path_str, ':');
	if (splited_paths == NULL)
		return (NULL);
	i = 0;
	res_path = check_access(splited_paths, cmd);
	return (res_path);
}
