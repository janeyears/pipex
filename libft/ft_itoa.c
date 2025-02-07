/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:43:18 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:35:06 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countdigit(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	numb;

	numb = n;
	len = ft_countdigit(n);
	if (n < 0)
		numb *= -1;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (numb == 0)
		str[0] = '0';
	else
	{
		while (len--, numb != 0)
		{
			str[len] = (numb % 10) + '0';
			numb = (numb - (numb % 10)) / 10;
		}
		if (n < 0)
			str[len] = '-';
	}
	return (str);
}
