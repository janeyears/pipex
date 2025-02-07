/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:00:03 by ekashirs          #+#    #+#             */
/*   Updated: 2025/01/17 11:36:10 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int search)
{
	while ((*str != '\0') && (*str != search))
	{
		str++;
	}
	if (*str == search)
	{
		return ((char *)str);
	}
	return (0);
}
