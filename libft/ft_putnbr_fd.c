/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:46:23 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:35:59 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	c;

	c = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		c = -c;
	}
	if (c >= 10)
		ft_putnbr_fd(c / 10, fd);
	ft_putchar_fd(c % 10 + '0', fd);
}
