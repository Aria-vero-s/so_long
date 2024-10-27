/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:10:04 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/06 15:21:46 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;
	size_t	j;

	src_len = 0;
	dst_len = 0;
	i = 0;
	j = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0' && dst_len < siz)
		dst_len++;
	if (siz <= dst_len)
		return (siz + src_len);
	i = dst_len;
	while (src[j] != '\0' && i < siz - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < siz)
		dst[i] = '\0';
	return (dst_len + src_len);
}
