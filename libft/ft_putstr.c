/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:45:23 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:47:06 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s, size_t *count)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (s == NULL)
		s = "(null)";
	while (s[i] != '\0')
	{
		res = ft_putchar(s[i], count);
		if (res == -1)
			return (-1);
		i++;
	}
	return (0);
}
