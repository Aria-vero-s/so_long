/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:09:59 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/06 15:23:51 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	else if (nmemb > SIZE_MAX / size)
		return (0);
	ptr = (int *)malloc(nmemb * size);
	if (ptr == NULL)
		return (0);
	i = 0;
	while (i < (nmemb * size))
	{
	*((char *)ptr + i) = 0;
		i++;
	}
	return (ptr);
}
