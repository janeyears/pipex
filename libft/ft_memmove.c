/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:48:35 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:35:46 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp_s;
	char	*temp_d;
	size_t	i;

	temp_s = (char *)src;
	temp_d = (char *)dest;
	i = 0;
	if (temp_d > temp_s)
	{
		while (n-- > 0)
			temp_d[n] = temp_s[n];
	}
	else
	{
		while (i < n)
		{
			temp_d[i] = temp_s[i];
			i++;
		}
	}
	return (dest);
}
