/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisascii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:06:47 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/13 18:08:21 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisascii(char *str)
{
	while (*str)
	{
		if (!ft_isascii(*str))
			return (0);
		str++;
	}
	return (1);
}
