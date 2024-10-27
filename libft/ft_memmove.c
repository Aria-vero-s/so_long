/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:10:37 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/06 15:21:12 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destt;
	char	*srcc;
	size_t	i;

	destt = (char *)dest;
	srcc = (char *)src;
	i = 0;
	if (destt == srcc || n == 0)
		return (dest);
	if (destt < srcc)
	{
		while (i < n)
		{
			destt[i] = srcc[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
		{
			destt[n] = srcc[n];
		}
	}
	return (dest);
}
