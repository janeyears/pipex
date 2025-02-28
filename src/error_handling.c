/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:47:01 by ekashirs          #+#    #+#             */
/*   Updated: 2025/02/28 14:19:26 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	error_free(int error_flag)
{
	if (error_flag == 1)
		ft_putendl_fd("CHANGE", 2);
	if (error_flag == 2)
		ft_putendl_fd("CHANGE", 2);
	exit(1);
}