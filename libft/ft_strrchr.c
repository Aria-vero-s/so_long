/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:52:02 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/06 15:22:06 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;
	int			len;

	ptr = s;
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	while (len >= 0)
	{
		if ((unsigned char)ptr[len] == (unsigned char)c)
			return ((char *)&ptr[len]);
		len--;
	}
	return (0);
}
