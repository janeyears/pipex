/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:56:06 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:36:25 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat( char *dest, const char *src, size_t size )
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len_s);
	if (size <= len_d)
		return (len_s + size);
	while (len_d + i < size - 1 && src[i] != '\0')
	{
		dest[len_d + i] = src[i];
		i++;
	}
	dest[len_d + i] = '\0';
	return (len_d + len_s);
}
