/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:45:01 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:36:42 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	c;
	size_t	n_len;
	char	*hay;

	i = 0;
	hay = (char *)dest;
	n_len = ft_strlen(src);
	if (n_len == 0 || dest == src)
		return (hay);
	while (hay[i] != '\0' && i < n)
	{
		c = 0;
		while (hay[i + c] != '\0' && src[c] != '\0'
			&& hay[i + c] == src[c] && i + c < n)
			c++;
		if (c == n_len)
			return (hay + i);
		i++;
	}
	return (0);
}
